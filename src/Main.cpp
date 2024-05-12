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

GameManager* gameManager;

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
	GameManager::cameraHeight = min(windowHeight * GameManager::CAMERA_HEIGHT_RATE, GameManager::mapHeight);
	GameManager::cameraWidth = min(windowWidth * GameManager::CAMERA_WIDTH_RATE, GameManager::mapWidth);

	gameManager = GameManager::getInstance();
	gameManager->setMap();

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

		gameManager->outputGameBoard();
		gameManager->setInformation();

		/*
		player[int(PLAYER::PLAYER1)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER1)] = false;

		player[int(PLAYER::PLAYER2)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER2)] = false;

		player[int(PLAYER::PLAYER3)] = true;
		gameManager.outputPlayerBoard(information, player);
		player[int(PLAYER::PLAYER3)] = false;*/

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
		switch (GameManager::gameStatus) 
		{
		case GAME_STATUS::MAP:
			gameManager->getCurrentRole()->move(-1, 0);
			break;
		case GAME_STATUS::BACKPACK:
			bag.chooseUp();
			break;
		}
	}
	else if (key[int(VALIDINPUT::ES)])
	{
		switch (GameManager::gameStatus) 
		{
		case GAME_STATUS::MAP:
			gameManager->getCurrentRole()->move(1, 0);
			break;
		case GAME_STATUS::BACKPACK:
			bag.chooseDown();
			break;
		}
	}
	else if (key[int(VALIDINPUT::EA)])
	{
		switch (GameManager::gameStatus) 
		{
		case GAME_STATUS::MAP:
			gameManager->getCurrentRole()->move(0, -1);
			break;
		}
	}
	else if (key[int(VALIDINPUT::ED)])
	{
		switch (GameManager::gameStatus) 
		{
		case GAME_STATUS::MAP:
			gameManager->getCurrentRole()->move(0, 1);
			break;
		}
	}
	else if (key[int(VALIDINPUT::EI)]) {
		switch (GameManager::gameStatus) 
		{
		case GAME_STATUS::MAP:
			bag.invMode();
			break;
		}
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		switch (GameManager::gameStatus)
		{
		case GAME_STATUS::BACKPACK:
			bag.useItem();
			break;
		}
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		switch (GameManager::gameStatus)
		{
		case GAME_STATUS::BACKPACK:
			bag.closeBag();
			break;
		}
	}
	else
	{
		std::cout << "invalid input\n";
	}
}