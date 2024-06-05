#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "GameManager.h"
#include "Backpack.h"
#include "Combat.h"
#include "Enemy.h"
#include "TeleportScroll.h"
using namespace std;

// Define input command
enum VALIDINPUT {
	EW = 0,
	ES,
	EA,
	ED,
	EI,
	EP,
	EBACKSPACE,
	EENTER,
	EESC,
	INVALID,
};

// Constant for time between updates
const double_t GTIMELOG = 0.03;

// Pointer to the game manager instance
GameManager* gameManager;

// Function prototypes
void keyUpdate(bool key[]);
void update(bool key[]);
void mapStatusUpdate(bool key[]);
void backpackStatusUpdate(bool key[]);
void interactiveStatusUpdate(bool key[]);

int main() {
	// Seed random number generator
	srand(time(NULL));

	// Get handle to the console window
	HWND hwndConsole = GetConsoleWindow();
	// Remove window decorations
	SetWindowLong(hwndConsole, GWL_STYLE, GetWindowLong(hwndConsole, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
	// Maximize the console window
	ShowWindow(hwndConsole, SW_MAXIMIZE);

	// Get console screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	// Initialize game manager window dimensions
	GameManager::windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	GameManager::windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	// Calculate camera dimensions based on window dimensions and rates
	GameManager::cameraHeight = min(GameManager::windowHeight * GameManager::CAMERA_HEIGHT_RATE, GameManager::mapHeight);
	GameManager::cameraWidth = min(GameManager::windowWidth * GameManager::CAMERA_WIDTH_RATE, GameManager::mapWidth);

	// Get singleton instance of GameManager and set up map
	gameManager = GameManager::getInstance();
	gameManager->setMap();

	// Initialize key state arrays
	bool gKeyState[int(VALIDINPUT::INVALID) + 1] = { false };

	double startT = clock();	// Start time for timing game loop
	double endT = clock();		// End time for timing game loop

	do
	{
		// Compute the time elapsed since last frame
		double timeFrame = (endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop if enough time has elapsed
		if (timeFrame >= GTIMELOG) {
			update(gKeyState);
			startT = clock(); // Reset start time
		}

		vector<Entity*> roles;
		roles.push_back(gameManager->getRole(0));
		roles.push_back(gameManager->getRole(1));
		roles.push_back(gameManager->getRole(2));

		// Render game board and set information
		gameManager->outputGameBoard();
		gameManager->setInformation();
		gameManager->setPlayerInformation(roles.size(), roles);

		// Update key state
		keyUpdate(gKeyState);
		endT = clock(); // Update end time
	} while (!gKeyState[int(VALIDINPUT::EESC)]); // Continue loop until ESC key is pressed

	return 0;
}


// Intent: Detect input value
// Pre: The array key
// Post: If key been push update that element true
void keyUpdate(bool key[]) {
	// Reset all elemnet false
	for (int i = 0; i < int(VALIDINPUT::INVALID); i++) {
		key[i] = false;
	}

	// Input
	char input = _getch();

	// Which been push, that one been true
	switch (input) {
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
	case 'P':
	case 'p':
		key[int(VALIDINPUT::EP)] = true;
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
void update(bool key[]) {
	// Check input wasd
	switch (GameManager::gameStatus) {
	case GAME_STATUS::MAP:
		mapStatusUpdate(key);
		break;
	case GAME_STATUS::BACKPACK:
		backpackStatusUpdate(key);
		break;
	case GAME_STATUS::INTERACTIVE:
		interactiveStatusUpdate(key);
		break;
	}
}

// Intent: Update the status of the player on the map based on user input.
// Pre: The `key` array must be initialized and contain valid input flags. The `gameManager` object and the current player role must be accessible.
// Post: Updates the player's position on the map or switches to the inventory mode based on user input.
void mapStatusUpdate(bool key[]) {
	// Move the player left on the map
	if (key[int(VALIDINPUT::EW)]) {
		gameManager->getCurrentRole()->move(-1, 0);
	}
	// Move the player right on the map
	else if (key[int(VALIDINPUT::ES)]) {
		gameManager->getCurrentRole()->move(1, 0);
	}
	// Move the player up on the map
	else if (key[int(VALIDINPUT::EA)]) {
		gameManager->getCurrentRole()->move(0, -1);
	}
	// Move the player down on the map
	else if (key[int(VALIDINPUT::ED)]) {
		gameManager->getCurrentRole()->move(0, 1);
	}
	// Switch to inventory mode
	else if (key[int(VALIDINPUT::EI)]) {
		bag.invMode();
	}
	else if (key[int(VALIDINPUT::EP)]) {
		gameManager->nextRole();
	}
	// Display message for invalid input
	else {
		std::cout << "Invalid Input";
	}
}

// Intent: Update the status of the backpack based on user input.
// Pre: The `key` array must be initialized and contain valid input flags. The `bag` object must be accessible.
// Post: Updates the status of the backpack, such as choosing items, using items, or closing the backpack, based on user input.
void backpackStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {
		// Move selection cursor up in the backpack
		bag.chooseUp();
	}
	else if (key[int(VALIDINPUT::ES)]) {
		// Move selection cursor down in the backpack
		bag.chooseDown();
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		// Use the selected item from the backpack
		bag.useItem(gameManager->getCurrentRole());
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		// Close the backpack
		bag.closeBag();
	}
	else {
		// Display message for invalid input
		std::cout << "Invalid Input";
	}
}

// Intent: Update the status of the interactive object based on user input.
// Pre: The `key` array must be initialized and contain valid input flags. The `gameManager` object must be accessible.
// Post: Updates the status of the interactive object, such as choosing actions, activating actions, or exiting, based on user input.
void interactiveStatusUpdate(bool key[]) {
	if (key[int(VALIDINPUT::EW)]) {
		// Move selection cursor up in the interactive object menu
		gameManager->getInteractiveObject()->chooseActiveUP();
	}
	else if (key[int(VALIDINPUT::ES)]) {
		// Move selection cursor down in the interactive object menu
		gameManager->getInteractiveObject()->chooseActiveDown();
	}
	else if (key[int(VALIDINPUT::EENTER)]) {
		// Activate the selected action
		gameManager->getInteractiveObject()->active(gameManager->getCurrentRole());
	}
	else if (key[int(VALIDINPUT::EBACKSPACE)]) {
		// Exit from the interactive object menu
		gameManager->getInteractiveObject()->exitActive(gameManager->getCurrentRole());
	}
	else {
		// Display message for invalid input
		std::cout << "Invalid Input";
	}
}
