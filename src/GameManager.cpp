#include "GameManager.h"
#include <iostream>
#include "Rect.h"
#include "Backpack.h"
#include "Role.h"
#include "Shop.h"
#include "ChestEvent.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"

// Define constants for camera height and width rates
const float GameManager::CAMERA_HEIGHT_RATE = 0.55;
const float GameManager::CAMERA_WIDTH_RATE = 0.66;

// Initialize static member variables
int GameManager::mapHeight = 50;
int GameManager::mapWidth = 140;
int GameManager::windowHeight = 0;
int GameManager::windowWidth = 0;
int GameManager::cameraHeight = 0;
int GameManager::cameraWidth = 0;
int GameManager::cameraX = 0;
int GameManager::cameraY = 0;

// Initialize the game status
GAME_STATUS GameManager::gameStatus;

// Initialize the game board with a 2D vector of Rect objects
std::vector<std::vector<Rect>> GameManager::gameBoard(mapHeight, std::vector<Rect>(mapWidth));

// Initialize the vector to store Role objects
std::vector<Role*> GameManager::roles;

// Pointer to the current role
Role* GameManager::currentRole;

// Pointer to the interactive object
Object* GameManager::interactiveObject;

// Initialize the singleton instance to NULL
GameManager* GameManager::instance = NULL;


// Intent: To retrieve the singleton instance of GameManager
// Pre: None
// Post: Returns the instance of GameManager
GameManager* GameManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}

// Intent: Constructor for GameManager class
// Pre: None
// Post: Initializes GameManager instance with roles and sets default values
GameManager::GameManager()
{
	for (int i = 0; i < 3; i++)
	{
		this->roles.push_back(new Role());
	}

	currentRole = roles[0];
	interactiveObject = NULL;
}

// Intent: Set text color in the console
// Pre: None
// Post: Text color in the console is changed
void GameManager::setColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// Intent: Set cursor position in the console
// Pre: None
// Post: Cursor position in the console is changed
void GameManager::setCursor(int y, int x)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(handle, pos);
}

// Intent: Set up the game map
// Pre: None
// Post: Game map is initialized with walls, shop, and initial role positions
void GameManager::setMap()
{
	//set wall
	for (int row = 9; row < mapHeight; row += 10)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			gameBoard[row][col].setCanPass((col % 10 == 9));
		}
	}

	//set shop
	gameBoard[15][65].setObject(new Shop());

	//set event
	gameBoard[15][63].setObject(new ChestEvent());

	// set 3 roles position
	roles[0]->setPos(25, 70);
	roles[1]->setPos(25, 72);
	roles[2]->setPos(27, 70);

	// set current role
	currentRole = roles[0];

	// set status
	gameStatus = GAME_STATUS::MAP;
}

// Intent: Retrieve a specific role by index
// Pre: None
// Post: Returns the role at the specified index
Role* GameManager::getRole(int i)
{
	return roles[i];
}

// Intent: Retrieve the current active role
// Pre: None
// Post: Returns the current active role
Role* GameManager::getCurrentRole()
{
	return currentRole;
}

// Intent: Retrieve the interactive object
// Pre: None
// Post: Returns the interactive object
Object* GameManager::getInteractiveObject()
{
	return interactiveObject;
}

// Intent: Set the interactive object
// Pre: None
// Post: Sets the interactive object to the specified object
void GameManager::setInteractiveObject(Object* o)
{
	interactiveObject = o;
}

// Intent: Determine if there is a direct line of sight between two positions on the game board
// Pre: The current and answer positions must be valid within the game board dimensions. The showBoard vector must be initialized with valid data.
// Post: Returns true if there is a direct line of sight between the two positions; otherwise, returns false.
bool GameManager::canSee(std::pair<int, int> current, std::pair<int, int> answer, std::vector<std::vector<std::pair<char, int>>>& showBoard)
{
	// Continuously move from the current position towards the answer position until reaching it
	while (!(current.first == answer.first && current.second == answer.second))
	{
		current.first += (current.first < answer.first) ? 1 : (current.first > answer.first) ? -1 : 0;
		current.second += (current.second < answer.second) ? 1 : (current.second > answer.second) ? -1 : 0;

		// Check if the current position is impassable
		if (!isPositionValid(current.first, current.second))
		{
			return false;
		}
	}
	return true;
}


// Intent: Set the camera position to focus on the current role within the map bounds
// Pre: The current role must be initialized, and the map dimensions and camera dimensions must be set.
// Post: Adjusts the camera position to ensure the current role is within the camera bounds.
void GameManager::setCameraToCurrentRole()
{
	cameraX = currentRole->getPos().second;
	cameraY = currentRole->getPos().first;

	// The X edge check whether touch the upper edge
	if (cameraX < cameraWidth / 2)
	{
		cameraX = cameraWidth / 2;
	}

	// The X edge check whether touch the down edge
	if (cameraX > mapWidth - cameraWidth / 2)
	{
		cameraX = mapWidth - cameraWidth / 2;
	}

	// The Y edge check whether touch the right edge
	if (cameraY < cameraHeight / 2)
	{
		cameraY = cameraHeight / 2;
	}

	// The Y edge check whether touch the left edge
	if (cameraY > mapHeight - cameraHeight / 2)
	{
		cameraY = mapHeight - cameraHeight / 2;
	}
}

// Intent: Set the information to be displayed based on the current game status
// Pre: None
// Post: Displays the appropriate information on the screen based on the current game status
void GameManager::setInformation()
{
	std::vector<std::string> information;

	switch (gameStatus)
	{
	case GAME_STATUS::MAP:
		information = normalInformation();
		break;
	case GAME_STATUS::BACKPACK:
		information = backpackInformation();
		break;
	case GAME_STATUS::INTERACTIVE:
		information = interactiveInformation();
		break;
	}

	outputInformation(information);
}

// Intent: Provide information about the game environment and player status
// Pre: None
// Post: Returns a vector of strings containing information about the game environment and player status
std::vector<std::string> GameManager::normalInformation()
{
	std::vector<std::string> information;
	information.push_back("Map height: " + std::to_string(mapHeight));
	information.push_back("Map width: " + std::to_string(mapWidth));
	information.push_back("Camera height: " + std::to_string(cameraHeight));
	information.push_back("Camera width: " + std::to_string(cameraWidth));
	information.push_back("Camera X: " + std::to_string(cameraX));
	information.push_back("Camera Y: " + std::to_string(cameraY));
	information.push_back("Current Role X: " + std::to_string(currentRole->getPos().second));
	information.push_back("Current Role Y: " + std::to_string(currentRole->getPos().first));

	std::string seperateLine = "";

	for (int i = 1; i < windowWidth - cameraWidth - 6; i++)
	{
		if (i == (windowWidth - cameraWidth - 6) / 2)
		{
			seperateLine += "Helper";
			continue;
		}
		seperateLine += "_";
	}

	information.push_back(seperateLine);
	information.push_back("Input 'I' to open backpack");
	information.push_back("Input 1,2,3 Display the player status");
	return information;
}

// Intent: Provide information about interactive objects
// Pre: None
// Post: Returns a vector of strings containing information about the interactive object
std::vector<std::string> GameManager::backpackInformation() 
{
	vector<string> information;
	information.push_back("Bag (Page:" + to_string(bag.getCurPage()) + "/" + to_string(bag.getMaxPage()) + ")");

	for (int i = (bag.getCurPage() - 1) * 8; i < bag.getCurPage() * 8; i++) 
	{
		if (i >= bag.getInventorySize())
		{
			information.push_back(" ");
			continue;
		}

		string printInformation = (bag.getCurIndex() == i ? "-> " : "   ");
		information.push_back(printInformation + bag.getItemName(i) + ": " + to_string(bag.getItemAmount(i)));
	}

	information.push_back(" "); // Seperate by 1 line
	string seperateLine = "";

	for (int i = 1; i < windowWidth - cameraWidth - 16; i++) 
	{
		if (i == (windowWidth - cameraWidth - 16) / 2)
		{
			seperateLine += "Item Description";
			continue;
		}

		seperateLine += "_";
	}

	information.push_back(seperateLine);
	information.push_back("To be countinue");

	return information;
}

// Intent: To generate information about the interactive object for display during gameplay interaction.
// Pre: The interactive object and its properties must be properly initialized. The bag object must be accessible.
// Post: Returns a vector of strings containing information about the interactive object, including available choices and page details.
std::vector<std::string> GameManager::interactiveInformation()
{
	// Get all available choices from the interactive object
	std::vector<std::string> choose = interactiveObject->getAllChoose();

	// Initialize vector to hold information to be displayed
	std::vector<std::string> information;

	// Calculate current page and maximum page
	int currentPage = interactiveObject->getChosenIndex() / 8;
	int maxPage = choose.size() / 8;
	int pageStartIndex = currentPage * 8; // Calculate the starting index for the current page

	// Add information about the interactive object and page number
	information.push_back(interactiveObject->getTag() + " (Page: " + std::to_string(currentPage + 1) + "/" + std::to_string(maxPage + 1) + ")");
	information.push_back("Your money: $" + std::to_string(bag.getMoney())); // Assuming `bag` is accessible
	information.push_back("------------");

	// Description
	information.push_back("Description:");
	information.push_back(interactiveObject->getDescription());
	information.push_back("------------");

	// Display available choices for the current page
	for (int i = pageStartIndex; i < pageStartIndex + 8 && i < choose.size(); i++)
	{
		// Check if the choice is the currently selected one
		if (i == interactiveObject->getChosenIndex())
		{
			information.push_back("-> " + choose[i]); // Mark the selected choice with "->"
		}
		else
		{
			information.push_back("   " + choose[i]); // Display other choices
		}
	}

	return information;
}

// Intent: Set the information of players for display
// Pre: None
// Post: Sets the player information and displays it on the screen
void GameManager::setPlayerInformation(int playerSize)
{
	for (int i = 0; i < playerSize; i++)
	{
		vector<string> info;
		char str[256];

		// Name information
		snprintf(str, sizeof(str), "Name: Player%d", i + 1);
		info.push_back(str);

		// HP and Focus information
		snprintf(str, sizeof(str), "HP: %d/%d, Focus: %d/%d", roles[i]->getHp(), roles[i]->getVitality(), roles[i]->getFocus(), roles[i]->getMaxFocus());
		info.push_back(str);

		// Physical ATK and DEF information
		snprintf(str, sizeof(str), "Physical ATK: %d, Physical DEF: %d", roles[i]->getPAttack(), roles[i]->getPDefense());
		info.push_back(str);

		// Magical ATK and DEF information
		snprintf(str, sizeof(str), "Magical ATK: %d, Magical DEF: %d", roles[i]->getMAttack(), roles[i]->getMDefense());
		info.push_back(str);

		// Speed and hit rate information
		snprintf(str, sizeof(str), "Speed: %d, HitRate: %d", roles[i]->getSpeed(), roles[i]->getHitRate());
		info.push_back(str);

		// Weapon information
		//snprintf(str, sizeof(str), "Weapon: %p", roles[i]->getWeaponName());
		info.push_back("Weapon: " + roles[i]->weapon->getName());

		info.push_back("Armor: " + roles[i]->armor->getName());
		info.push_back("Accessory: " + roles[i]->acc->getName());
		info.push_back("Buff: ");

		outputPlayerBoard(info, i);
	}
}

// Intent: Output the player board to the console
// Pre: None
// Post: Displays the player board to the console
void GameManager::outputPlayerBoard(std::vector<std::string>& information, int playerPointer)
{
	// The board information
	for (int row = 0; row < windowHeight / 3; row += 1)
	{
		// The row start postion
		setCursor(windowHeight / 3 * 2 + row, windowWidth / 3 * playerPointer + 2);
		std::cout << "|";

		for (int col = 0; col < windowWidth / 4 + 5; col += 1)
		{
			std::cout << ((row == 0 || row == windowHeight / 3 - 1) ? "-" : " ");
		}

		// The row end position
		std::cout << "|";

		// Print each information in enemy board
		setCursor(windowHeight / 3 * 2 + row, windowWidth / 3 * playerPointer + 3);
		if (row > 0 && row < windowHeight / 3 - 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

// Intent: Set the information of enemies for display
// Pre: None
// Post: Sets the enemy information and displays it on the screen
void GameManager::setEnemyInformation(int playerSize)
{
	for (int i = 0; i < playerSize; i++)
	{
		vector<string> info;
		char str[256];

		// Name information
		snprintf(str, sizeof(str), "Name: Enemy: %d", i);
		info.push_back(str);

		// HP and Focus information
		snprintf(str, sizeof(str), "HP: %d/%d, Focus: %d/%d", roles[i]->getHp(), roles[i]->getVitality(), roles[i]->getFocus(), roles[i]->getMaxFocus());
		info.push_back(str);

		// Physical ATK and DEF information
		snprintf(str, sizeof(str), "Physical ATK: %d, Physical DEF: %d", roles[i]->getPAttack(), roles[i]->getPDefense());
		info.push_back(str);

		// Magical ATK and DEF information
		snprintf(str, sizeof(str), "Magical ATK: %d, Magical DEF: %d", roles[i]->getMAttack(), roles[i]->getMDefense());
		info.push_back(str);

		// Speed and hit rate information
		snprintf(str, sizeof(str), "Speed: %d, HitRate: %d", roles[i]->getSpeed(), roles[i]->getHitRate());
		info.push_back(str);

		// Weapon information
		//snprintf(str, sizeof(str), "Weapon: %d", roles[i]->getWeaponName());
		info.push_back("Weapon: " + roles[i]->weapon->getName());
		info.push_back("Armor: " + roles[i]->armor->getName());
		info.push_back("Accessory: " + roles[i]->acc->getName());
		info.push_back("Buff: ");

		outputEnemyBoard(info, i);
	}
}


// Intent: Output the enemy board to the console
// Pre: None
// Post: Displays the enemy board to the console
void GameManager::outputEnemyBoard(std::vector<std::string>& information, int playerPointer)
{
	// The board information
	for (int row = 0; row < windowHeight / 3; row += 1)
	{
		// The row start postion
		setCursor(row, windowWidth / 3 * playerPointer + 2);
		std::cout << "|";

		for (int col = 0; col < windowWidth / 4 + 5; col += 1)
		{
			std::cout << ((row == 0 || row == windowHeight / 3 - 1) ? "-" : " ");
		}

		// The row end position
		std::cout << "|";

		// Print each information in enemy board
		setCursor(row, windowWidth / 3 * playerPointer + 3);
		if (row > 0 && row < windowHeight / 3 - 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

// Intent: Display the battle screen
// Pre: None
// Post: Displays the battle screen and handles player input
void GameManager::battleScreen(std::vector<Entity*> player, std::vector<Entity*> enemy, std::vector<std::string> list, std::vector<std::string> data)
{
	// The enemey and player information display
	system("CLS");
	setEnemyInformation(enemy.size());
	setPlayerInformation(player.size());

	// The choose board display
	for (int row = 0; row < windowHeight / 3; row += 1)
	{
		setCursor(row + windowHeight / 3, 2);
		std::cout << "|";

		for (int col = 0; col < windowWidth - 5; col += 1)
		{
			std::cout << ((row == 0 || row == windowHeight / 3 - 1) ? "-" : " ");
		}
		std::cout << "|";
	}

	char input;
	int chocie = 0;
	do
	{
		// The mode information
		for (int i = 0; i < list.size(); i += 1)
		{
			setCursor(windowHeight / 3 + i + 1, 3);
			if (i == chocie)
			{
				cout << "->";
			}
			else
			{
				cout << "  ";
			}
			cout << list[i];
		}

		// The description information
		for (int i = 0; i < data.size(); i += 1)
		{
			setCursor(windowHeight / 3 + i + 1, cameraX / 2);
			cout << data[i];
		}

		// Let user input the w/s to choose the mode
		input = _getch();
		switch (input)
		{
		case 'w':
			chocie = (chocie < 1 ? 1 : chocie - 1);
			break;
		case 's':
			chocie = (chocie > list.size() ? chocie : chocie + 1);
		}

	} while (input != '\r');
}

// Intent: Output the game board to the console
// Pre: None
// Post: Displays the game board to the console
void GameManager::outputGameBoard()
{
	char icon = currentRole->getIcon();
	std::pair<int, int> pos = currentRole->getPos();

	setCameraToCurrentRole();

	// set up show board, 2D vector has pair, it has char and color
	std::vector<std::vector<std::pair<char, int>>> showBoard(mapHeight, std::vector<std::pair<char, int>>(mapWidth, std::pair<char, int>('.', 96)));

	for (int row = 0; row < mapHeight; row += 1)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			// If the gameboard get isn't visible
			if (!gameBoard[row][col].getIsVisible())
			{
				// The range in player can see range
				if (pow(pos.first - row, 2) + pow(pos.second - col, 2) < pow(10, 2))
				{
					// If the Position without the block and see direction
					if (canSee(std::pair<int, int>(row, col), pos, showBoard))
					{
						gameBoard[row][col].setIsVisible(true);
					}
				}	
			}

			// set icon
			std::pair<char, int> icon = gameBoard[row][col].getIcon();
			showBoard[row][col].first = icon.first;
			showBoard[row][col].second = icon.second;
		}
	}

	showBoard[pos.first][pos.second].second = 108;

	// The loop check each board need to be show
	for (int i = 0; i < roles.size(); i++) 
	{
		pos = roles[i]->getPos();
		showBoard[pos.first][pos.second].first = icon;
	}

	// print out rolled map
	int marginUp = cameraY - cameraHeight / 2;
	int marginDown = cameraY + cameraHeight / 2;
	int marginLeft = cameraX - cameraWidth / 2;
	int marginRight = cameraX + cameraWidth / 2;

	// The output board
	for (int row = 0; row < cameraHeight + 2; row += 1) 
	{
		setCursor(row, 0);
		std::cout << "|";

		for (int col = marginLeft; col < marginRight; col += 1)
		{
			if (row == 0 || row == cameraHeight + 1) 
			{
				std::cout << "-";
			}
			else if (row + marginUp - 1 < mapHeight)
			{
				setColor(showBoard[marginUp + row - 1][col].second);
				std::cout << showBoard[marginUp + row - 1][col].first;
				setColor();
			}
		}
		std::cout << "|";
	}
}

// Intent: Output information to the console
// Pre: None
// Post: Displays information to the console
void GameManager::outputInformation(std::vector<std::string>& information)
{
	for (int row = 0; row < cameraHeight + 2; row += 1)
	{
		// Output the edge 
		setCursor(row, cameraWidth);
		std::cout << "|";

		for (int col = 1; col < windowWidth - cameraWidth - 1; col += 1)
		{
			if (row == 0 || row == cameraHeight + 1)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << " ";
			}
		}

		std::cout << "|";
		setCursor(row, cameraWidth + 1);

		// Print the information in board
		if (row > 0 && row < cameraHeight + 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

// Intent: Check if a position is valid on the game map
// Pre: None
// Post: Returns true if the position is valid, false otherwise
bool GameManager::isPositionValid(int y, int x) {
	if (y > (mapHeight - 1) || x > (mapWidth - 1) || y < 0 || x < 0)
	{
		return false;
	}

	return (gameBoard[y][x].getCanPass());
}