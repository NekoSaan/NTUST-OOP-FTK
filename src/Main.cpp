#include "Main.h"
#include "Backpack.h"
using namespace std;

vector<vector<Rect>> map(mapHeight, vector<Rect>(mapWidth));

Object gObject;

int main(void) {
    HWND hwndConsole = GetConsoleWindow();
    SetWindowLong(hwndConsole, GWL_STYLE, GetWindowLong(hwndConsole, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwndConsole, SW_MAXIMIZE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	cameraHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	cameraWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	
	cameraX = 0;
	cameraY = 0;

	setMap();

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
		outputInformation();

		vector<string> information;
		information.push_back("MapSize_Row: " + to_string(mapHeight));
		information.push_back("MapSize_Col: " + to_string(mapWidth));
		information.push_back("Camera Y: " + to_string(cameraY));
		information.push_back("Camera X: " + to_string(cameraX));
		information.push_back("Object Y: " + to_string(gObject.getPos().y));
		information.push_back("Object X: " + to_string(gObject.getPos().x));

		information.push_back("Camera height: " + to_string(cameraHeight));
		information.push_back("Camera width: " + to_string(cameraWidth));

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
	for (int row = 9; row < mapHeight; row += 10)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			map[row][col].setStatus((col % 10 == 9) ? '.' : '#');
		}
	}

	gObject.setPos(Point{ cameraHeight / 2, cameraWidth / 3 });
}

void outputMap()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(handle, pos);

	vector<vector<string>> showBoard(mapHeight, vector<string>(mapWidth, "."));

	for (int row = 0; row < mapHeight; row += 1)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			showBoard[row][col] = map[row][col].getStatus();
		}
	}

	Point charPos = gObject.getPos();
	showBoard[charPos.y][charPos.x] = gObject.getTag();

	for (int row = 0; row < cameraHeight - 1; row += 1)
	{
		for (int col = 0; col < cameraWidth / 3 * 2; col += 1)
		{
			setColor(showBoard[row + cameraY][col + cameraX] == "." ? 7 : 224);
			cout << showBoard[row + cameraY][col + cameraX];
			setColor();
		}
		cout << "\n";
	}
}

void outputInformation()
{
	for (int row = 0; row < cameraHeight - 1; row += 1)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = cameraWidth / 3 * 2;
		pos.Y = row;
		SetConsoleCursorPosition(handle, pos);

		cout << "#";

		for (int col = 0; col < cameraWidth / 3 - 2; col += 1)
		{
			cout << (row == 0 || row == cameraHeight - 2 ? "#" : " ");
		}

		cout << "#";
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
	case 'I':
	case 'i':
		key[int(VALIDINPUT::EI)] = true;
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
	// Check input wasd
	if (key[int(VALIDINPUT::EW)])
	{
		gObject.ObjectMove(Point{ -1,0 });
	}
	else if (key[int(VALIDINPUT::ES)])
	{
		gObject.ObjectMove(Point{ 1,0 });
	}
	else if (key[int(VALIDINPUT::EA)])
	{
		gObject.ObjectMove(Point{ 0,-1 });
	}
	else if (key[int(VALIDINPUT::ED)])
	{
		gObject.ObjectMove(Point{ 0,1 });
	}
	else if (key[int(VALIDINPUT::EI)]) {
		bag.invMode();
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
		pos.X = (cameraWidth / 3 + 1) * 2;
		pos.Y = (1 + row);
		SetConsoleCursorPosition(handle, pos);

		cout << information[row];
	}

	pos.X = 0;
	pos.Y = cameraHeight;
	SetConsoleCursorPosition(handle, pos);
}