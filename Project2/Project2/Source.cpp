#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "Character.h"
using namespace std;

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

const Point MAPSIZE = Point{ 1000,1000 };

Point consoleSize, currentPoint;

const double_t GTIMELOG = 0.33;

Character gCharacter;

static vector<vector<char>> gBoard;

void setColor(int color = 7);

void setMap();

void outputMap();

void keyUpdate(bool key[]);

void update(bool key[]);

void informationShow(vector<string> information);

int main() {
    HWND hwndConsole = GetConsoleWindow();
    SetWindowLong(hwndConsole, GWL_STYLE, GetWindowLong(hwndConsole, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwndConsole, SW_MAXIMIZE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	consoleSize.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	consoleSize.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	currentPoint.x = 0;
	currentPoint.y = 0;


	setMap();

	bool gKeyState[int(VALIDINPUT::INVALID) + 1] = { false };
	double startT = clock();
	double endT = clock();

	do
	{
		// Compute the time lap
		double timeFrame = (endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= GTIMELOG)
		{
			update(gKeyState);
			startT = clock();
		}

		outputMap();

		vector<string> information;
		information.push_back("MapSize_Row: " + to_string(MAPSIZE.y));
		information.push_back("MapSize_Col: " + to_string(MAPSIZE.x));
		information.push_back("Current Y: " + to_string(currentPoint.y));
		information.push_back("Current X: " + to_string(currentPoint.x));
		information.push_back("Character Y: " + to_string(gCharacter.getPos().y));
		information.push_back("Character X: " + to_string(gCharacter.getPos().x));

		information.push_back("ConsoleSize Y: " + to_string(consoleSize.y));
		information.push_back("ConsoleSize X: " + to_string(consoleSize.x));

		informationShow(information);

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EESC)]);

    return 0;
}

void setColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void setMap()
{
	gBoard.resize(MAPSIZE.y, vector<char>(MAPSIZE.x, '.'));

	for (int row = 9; row < consoleSize.y; row += 10)
	{
		for (int col = 0; col < consoleSize.x; col += 1)
		{
			gBoard[row][col] = ((col % 10 == 9) ? '.' : '#');
		}
	}

	gCharacter.setPos(Point{ consoleSize.y / 2, consoleSize.x / 3 });
}

void outputMap()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(handle, pos);

	int gameBoard = consoleSize.x / 3 * 2;
	int infoBoard = consoleSize.x / 3;


	vector<vector<char>> showBoard(MAPSIZE.y, vector<char>(MAPSIZE.x, '.'));
	for (int row = 0; row < consoleSize.y; row += 1)
	{
		for (int col = 0; col < consoleSize.x; col += 1)
		{
			showBoard[row][col] = gBoard[row][col];
		}
	}

	Point charPos = gCharacter.getPos();
	showBoard[charPos.y][charPos.x] = gCharacter.getStatus();

	for (int row = 0; row < consoleSize.y - 1; row += 1)
	{
		for (int col = 0; col < gameBoard; col += 1)
		{
			setColor(showBoard[row + currentPoint.y][col + currentPoint.x] == '.' ? 7 : 224);
			cout << showBoard[row + currentPoint.y][col + currentPoint.x];
			setColor();
		}

		cout << "#";
		for (int col = 0; col < infoBoard - 2; col += 1)
		{
			cout << (row == 0 || row == consoleSize.y - 2 ? "#" : " ");
		}
		cout << "#\n";
	}
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
		gCharacter.characterMove(Point{ -1,0 }, MAPSIZE, currentPoint, consoleSize);
	}
	else if (key[int(VALIDINPUT::ES)])
	{
		gCharacter.characterMove(Point{ 1,0 }, MAPSIZE, currentPoint, consoleSize);
	}
	else if (key[int(VALIDINPUT::EA)])
	{
		gCharacter.characterMove(Point{ 0,-1 }, MAPSIZE, currentPoint, consoleSize);
	}
	else if (key[int(VALIDINPUT::ED)])
	{
		gCharacter.characterMove(Point{ 0,1 }, MAPSIZE, currentPoint, consoleSize);
	}
	else
	{
		std::cout << "invalid input\n";
	}
}

void informationShow(vector<string> information)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int row = 0; row < information.size(); row += 1)
	{
		pos.X = (consoleSize.x / 3 + 1) * 2;
		pos.Y = (1 + row);
		SetConsoleCursorPosition(handle, pos);

		cout << information[row];
	}

	pos.X = 0;
	pos.Y = consoleSize.y;
	SetConsoleCursorPosition(handle, pos);
}