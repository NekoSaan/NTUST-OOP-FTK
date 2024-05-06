#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <conio.h>
#include <random>
using namespace std;

static int screenHeight;
static int screenWidth;

static int charHeight;
static int charWidth;

static int mapPointerX = 0;
static int mapPointerY = 0;

static int characterX = 0;
static int characterY = 0;

int xLen = 150;
int yLen = 50;

// Define input command
enum class VALIDINPUT
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	EESC = 4,
	INVALID,
};

static vector<vector<char>> gBoard;

void SetColor(int color = 7);

void outputMap();

void informationShow(vector<string> information);

void keyUpdate(bool key[]);

void update(bool key[]);

void rangeCheck(char mode, char alex);

int main()
{
	srand(unsigned(time));
	HDC hdc = GetDC(NULL);
	HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"));

	SelectObject(hdc, hFont);

	SIZE size;
	const char* text = "＃";
	GetTextExtentPoint32(hdc, "＃", strlen(text), &size);

	charHeight = size.cy;
	charWidth = size.cx;
	
	ReleaseDC(NULL, hdc);
	DeleteObject(hFont);

	screenWidth = GetSystemMetrics(SM_CXSCREEN) / charWidth;
	screenHeight = GetSystemMetrics(SM_CYSCREEN) / charHeight;

	/*std::cout << "Character height: " << size.cy << std::endl;
	std::cout << "Character width: " << size.cx << std::endl;
	std::cout << "Screen height: " << screenHeight << std::endl;
	std::cout << "Screen width: " << screenWidth << std::endl;*/

	characterX = screenWidth / 3;
	characterY = screenHeight / 2;
	mapPointerX = screenWidth / 3;
	mapPointerY = screenHeight / 2;

	/*do
	{
		printf("Input map yLength : ");
		cin >> yLen;
		printf("Input map xLength : ");
		cin >> xLen;
		system("CLS");
	} while (xLen < 140 || yLen < 50);
	*/

	gBoard.resize(yLen, vector<char>(xLen, '.'));
	for (int row = 0; row < yLen; row += 10)
	{
		for (int col = 0; col < xLen; col++)
		{
			if (col % 9 != 0 && col != 0)
			{
				gBoard[row][col] = '#';
			}
		}
	}
	bool gKeyState[int(VALIDINPUT::INVALID) + 1] = { false };

	// Variable for game loop
	double startT = clock();
	double endT = clock();

	do
	{
		// Compute the time lap
		double timeFrame = (endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		update(gKeyState);

		outputMap();

		vector<string> information;
		information.push_back("MapSize_Row: " + to_string(yLen));
		information.push_back("MapSize_Col: " + to_string(xLen));
		information.push_back("Current Y: " + to_string(characterY));
		information.push_back("Current X: " + to_string(characterX));

		informationShow(information);
		
		
		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EESC)]);
}

void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void outputMap()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(handle, pos);

	int mapX = characterX, mapY = characterY;
	if (mapY + screenHeight >= yLen)
	{
		mapY = yLen - screenHeight;
	}

	if (mapX + (screenWidth * 2 / 3) >= xLen)
	{
		mapX = xLen - (screenWidth * 2 / 3);
	}

	for (int i = 0; i < screenHeight; i += 1)
	{
		for (int j = 0; j < (screenWidth * 2 / 3); j += 1)
		{
			SetColor(((gBoard[i + mapY][j + mapX] == '.') ? 224 : 136));
			std::cout << ((gBoard[i + mapY][j + mapX] == '.') ? "．" : "　");
			SetColor();
		}
		cout << "＃";
		for (int j = 0; j < screenWidth / 3; j += 1)
		{
			std::cout << ((i == 0 || i == screenHeight - 1) ? "＃" : "　");
		}
		cout << "＃\n";
	}

	pos.X = mapPointerX;
	pos.Y = mapPointerY;
	SetConsoleCursorPosition(handle, pos);
	SetColor(224);
	cout << "Ｈ";
	SetColor(7);
}

void informationShow(vector<string> information)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int row = 0; row < information.size(); row += 1)
	{
		pos.X = (screenWidth / 3 * 2 + 1) * 2;
		pos.Y = (1 + row);
		SetConsoleCursorPosition(handle, pos);

		cout << information[row];
	}

	pos.X = 0;
	pos.Y = screenHeight;
	SetConsoleCursorPosition(handle, pos);
}

// Intent: Detect input value
// Pre: The array key
// Post: If key been push update that element true
void keyUpdate(bool key[])
{
	// Reset all elemnet false
	for (int i = 0; i < int(VALIDINPUT::INVALID); i++)
	{
		key[i] = false;
	}

	// Input
	char input = _getch();

	// Which been push, that one been true
	switch (input)
	{
	case 'W':
	case 'w':
		key[int(VALIDINPUT::EW)] = true;
		break;
	case 'S':
	case 's':
		key[int(VALIDINPUT::ES)] = true;
		break;
	case 'A':
	case 'a':
		key[int(VALIDINPUT::EA)] = true;
		break;
	case 'D':
	case 'd':
		key[int(VALIDINPUT::ED)] = true;
		break;
	case 27:
		key[int(VALIDINPUT::EESC)] = true;
		break;
	default:
		key[int(VALIDINPUT::INVALID)] = true;
	}
}

// Intent: Update output information
// Pre: The key array
// Post: Output new inforamtion contain hero, creature move
void update(bool key[])
{
	// Clear all ouput
	system("CLS");

	// Check input wasd
	if (key[int(VALIDINPUT::EW)])
	{
		rangeCheck('s', 'y');
		characterY -= 1;
	}
	else if (key[int(VALIDINPUT::ES)])
	{
		rangeCheck('a', 'y');
		characterY += 1;
	}
	else if (key[int(VALIDINPUT::EA)])
	{
		rangeCheck('s', 'x');
		characterX -= 1;
	}
	else if (key[int(VALIDINPUT::ED)])
	{
		rangeCheck('a', 'x');
		characterX += 1;
	}
	else
	{
		std::cout << "invalid input\n";
	}
	
	characterY = (characterY >= yLen ? yLen : characterY);
	characterY = (characterY < 0 ? 0 : characterY);
	characterX = (characterX >= xLen ? xLen : characterX);
	characterX = (characterX < 0 ? 0 : characterX);
}

void rangeCheck(char mode, char alex)
{
	// Add
	if (mode == 'a' && alex == 'y')
	{	
		if (characterY > yLen - (screenHeight / 2))
		{
			mapPointerY = (mapPointerY < (screenHeight - 1) ? mapPointerY + 1 : mapPointerY);
		}

		if (mapPointerY < (screenHeight / 2 - 1))
		{
			mapPointerY = mapPointerY + 1;
		}
	}
	if (mode == 'a' && alex == 'x')
	{
		if (characterX > xLen - (screenWidth / 3))
		{
			mapPointerX = (mapPointerX < ((screenWidth * 2 / 3) - 1) ? mapPointerX + 1 : mapPointerX);
		}

		if (characterX < (screenWidth / 3 - 1))
		{
			mapPointerX = mapPointerX + 1;
		}
	}
	if (mode == 's' && alex == 'y')
	{
		if (characterY < (screenHeight / 2 - 1))
		{
			mapPointerY = (mapPointerY > 0 ? mapPointerY - 1 : mapPointerY);
		}

		if (characterY > yLen - (screenHeight / 2 + 1))
		{
			mapPointerY = mapPointerY - 1;
		}
	}
	if (mode == 's' && alex == 'x')
	{
		if (characterX < (screenWidth / 3 - 1))
		{
			mapPointerX = (mapPointerX > 0 ? mapPointerX - 1 : mapPointerX);
		}

		if (characterX > xLen - (screenWidth / 3 - 1))
		{
			mapPointerX = mapPointerX - 1;
		}
	}
}
