#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "GameManager.h"
#include "Backpack.h"
using namespace std;

// Define input command
enum VALIDINPUT
{
	EW = 0,
	ES,
	EA,
	ED,
	EI,
	EBACKSPACE,
	EENTER,
	EESC,
	INVALID,
};

const double_t GTIMELOG = 0.03;

GameManager gameManager;

void keyUpdate(bool key[]);

void update(bool key[]);

int main() {
    HWND hwndConsole = GetConsoleWindow();
    SetWindowLong(hwndConsole, GWL_STYLE, GetWindowLong(hwndConsole, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwndConsole, SW_MAXIMIZE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	GameManager::cameraHeight = windowHeight * GameManager::CAMERA_HEIGHT_RATE;
	GameManager::cameraWidth = windowWidth * GameManager::CAMERA_WIDTH_RATE;

	gameManager.setMap();

	bool gKeyState[int(VALIDINPUT::INVALID) + 1] = { false };
	bool player[int(PLAYER::INVALID)] = { false };

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

		gameManager.outputGameBoard(player1.getTag(), player1.getPos());

		vector<string> information;
		information.push_back("Camera height: " + to_string(cameraHeight));
		information.push_back("Camera width: " + to_string(cameraWidth));

		gameManager.outputInformation(information);

		player[int(PLAYER::PLAYER1)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER1)] = false;

		player[int(PLAYER::PLAYER2)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER2)] = false;

		player[int(PLAYER::PLAYER3)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER3)] = false;

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EESC)]);

    return 0;
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
	case 8:
		key[int(VALIDINPUT::EBACKSPACE)] = true;
		break;
	case 13:
		key[int(VALIDINPUT::EENTER)] = true;
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
		GameManager::currentRole->ObjectMove(-1, 0);
	}
	else if (key[int(VALIDINPUT::ES)])
	{
		GameManager::currentRole->ObjectMove(1, 0);
	}
	else if (key[int(VALIDINPUT::EA)])
	{
		GameManager::currentRole->ObjectMove(0, -1);
	}
	else if (key[int(VALIDINPUT::ED)])
	{
		GameManager::currentRole->ObjectMove(0, 1);
	}
	else if (key[int(VALIDINPUT::EI)]) {
		bag.invMode();
	}
	else
	{
		std::cout << "invalid input\n";
	}
}