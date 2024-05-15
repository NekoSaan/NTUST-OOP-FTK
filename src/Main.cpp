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

void keyUpdate(bool key[], bool playerKey[]);

void update(bool key[], bool playerKey[]);
void mapStatusUpdate(bool key[]);
void combatStatusUpdate(bool key[]);
void backpackStatusUpdate(bool key[]);
void interactiveStatusUpdate(bool key[]);

int main() {
	HWND hwndConsole = GetConsoleWindow();
    SetWindowLong(hwndConsole, GWL_STYLE, GetWindowLong(hwndConsole, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwndConsole, SW_MAXIMIZE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	GameManager::windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GameManager::windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	GameManager::cameraHeight = min(GameManager::windowHeight * GameManager::CAMERA_HEIGHT_RATE, GameManager::mapHeight);
	GameManager::cameraWidth = min(GameManager::windowWidth * GameManager::CAMERA_WIDTH_RATE, GameManager::mapWidth);

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
			update(gKeyState, player);
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
		player[int(PLAYER::PLAYER3)] = false;
		*/

		// Update the key
		keyUpdate(gKeyState, player);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EESC)]);

    return 0;
}

// Intent: Detect input value
// Pre: The array key
// Post: If key been push update that element true
void keyUpdate(bool key[], bool playerKey[])
{
	// Reset all elemnet false
	for (int i = 0; i < int(VALIDINPUT::INVALID); i++)
	{
		key[i] = false;
	}

	// Reset all player elemnet false
	for (int i = 0; i < int(PLAYER::INVALID); i++)
	{
		playerKey[i] = false;
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
	case '1':
		playerKey[int(PLAYER::PLAYER1)] = true;
		break;
	case '2':
		playerKey[int(PLAYER::PLAYER2)] = true;
		break;
	case '3':
		playerKey[int(PLAYER::PLAYER3)] = true;
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
void update(bool key[], bool playerKey[])
{
	// Check input wasd
	switch (GameManager::gameStatus) {
		case GAME_STATUS::MAP:
			mapStatusUpdate(key);
			break;
		case GAME_STATUS::COMBAT:
			combatStatusUpdate(key);
			break;
		case GAME_STATUS::BACKPACK:
			backpackStatusUpdate(key);
			break;
		case GAME_STATUS::INTERACTIVE:
			interactiveStatusUpdate(key);
			break;
	}

	if (playerKey[int(PLAYER::PLAYER1)])
	{
		vector<string> information(2, " ");

		information[0] = "Player 1 : ";
		information[1] = "Status : ";
		gameManager->outputPlayerBoard(information, playerKey);
	}
	else if (playerKey[int(PLAYER::PLAYER2)])
	{
		vector<string> information(2, " ");

		information[0] = "Player 2 : ";
		information[1] = "Status : ";
		gameManager->outputPlayerBoard(information, playerKey);
	}
	else if (playerKey[int(PLAYER::PLAYER3)])
	{
		vector<string> information(2, " ");

		information[0] = "Player 3 : ";
		information[1] = "Status : ";
		gameManager->outputPlayerBoard(information, playerKey);
	}
	else
	{
		//std::cout << "invalid input\n";
	}
}

void mapStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {
		gameManager->getCurrentRole()->move(-1, 0);
	}
	else if (key[int(VALIDINPUT::ES)]) {
		gameManager->getCurrentRole()->move(1, 0);
	}
	else if (key[int(VALIDINPUT::EA)]) {
		gameManager->getCurrentRole()->move(0, -1);
	}
	else if (key[int(VALIDINPUT::ED)]) {
		gameManager->getCurrentRole()->move(0, 1);
	}
	else if (key[int(VALIDINPUT::EI)]) {
		bag.invMode();
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		//nothing
	}
	else
	{
		std::cout << "invalid input\n";
	}
}

void combatStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {

	}
	else if (key[int(VALIDINPUT::ES)]) {

	}
	else if (key[int(VALIDINPUT::EA)]) {

	}
	else if (key[int(VALIDINPUT::ED)]) {

	}
	else if (key[int(VALIDINPUT::EI)]) {

	}
	else if (key[int(VALIDINPUT::EENTER)]) {

	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {

	}
	else
	{
		std::cout << "invalid input\n";
	}
}

void backpackStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {
		bag.chooseUp();
	}
	else if (key[int(VALIDINPUT::ES)]) {
		bag.chooseDown();
	}
	else if (key[int(VALIDINPUT::EA)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::ED)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::EI)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		bag.useItem();
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		bag.closeBag();
	}
	else
	{
		std::cout << "invalid input\n";
	}
}

void interactiveStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {
		gameManager->getInteractiveObject()->chooseActiveUP();
	}
	else if (key[int(VALIDINPUT::ES)]) {
		gameManager->getInteractiveObject()->chooseActiveDown();
	}
	else if (key[int(VALIDINPUT::EA)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::ED)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::EI)]) {
		//nothing
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		gameManager->getInteractiveObject()->active(gameManager->getCurrentRole());
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		gameManager->getInteractiveObject()->exitActive();
	}
	else
	{
		std::cout << "invalid input\n";
	}
}