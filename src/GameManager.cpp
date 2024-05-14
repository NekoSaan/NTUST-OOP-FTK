#include "GameManager.h"
#include <iostream>
#include "Rect.h"
#include "Object.h"
#include "Backpack.h"
#include "Role.h"
const float GameManager::CAMERA_HEIGHT_RATE = 0.55;
const float GameManager::CAMERA_WIDTH_RATE = 0.66;

int GameManager::mapHeight = 50;
int GameManager::mapWidth = 140;
int GameManager::cameraHeight = 0;
int GameManager::cameraWidth = 0;
int GameManager::cameraX = 0;
int GameManager::cameraY = 0;

GAME_STATUS GameManager::gameStatus;

std::vector<std::vector<Rect>> GameManager::gameBoard(mapHeight, std::vector<Rect>(mapWidth));

std::vector<Role*> GameManager::roles;
Role* GameManager::currentRole;

GameManager* GameManager::instance = NULL;

GameManager* GameManager::getInstance() {
	if (instance == NULL) {
		instance = new GameManager();
	}

	return instance;
}

GameManager::GameManager() {
	for (int i = 0; i < 3; i++) {
		this->roles.push_back(new Role());
	}

	currentRole = roles[0];
}

void GameManager::setColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void GameManager::setCursor(int y, int x)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(handle, pos);
}

void GameManager::setMap()
{
	for (int row = 9; row < mapHeight; row += 10)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			gameBoard[row][col].setCanPass((col % 10 == 9));
		}
	}

	// set 3 roles position
	roles[0]->setPos(25, 70);
	roles[1]->setPos(25, 72);
	roles[2]->setPos(27, 70);

	// set current role
	currentRole = roles[0];

	// set status
	gameStatus = GAME_STATUS::MAP;
}

Role* GameManager::getRole(int i) {
	return roles[i];
}

Role* GameManager::getCurrentRole() {
	return currentRole;
}

void GameManager::outputGameBoard()
{
	char icon = currentRole->getIcon();
	std::pair<int, int> pos = currentRole->getPos();

	setCameraToCurrentRole();

	//set up show board, 2D vector has pair, it has char and color
	std::vector<std::vector<std::pair<char, int>>> showBoard(mapHeight, std::vector<std::pair<char, int>>(mapWidth, std::pair<char, int>('.', 96)));
	
	for (int row = 0; row < mapHeight; row += 1)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			// set rect isVisible
			if (!gameBoard[row][col].getIsVisible() &&
				pow(pos.first - row, 2) + pow(pos.second - col, 2) < pow(10, 2) &&
				canSee(std::pair<int, int>(row, col), pos, showBoard)) {
				gameBoard[row][col].setIsVisible(true);
			}

			// set icon
			std::pair<char, int> icon = gameBoard[row][col].getIcon();
			showBoard[row][col].first = icon.first;
			showBoard[row][col].second = icon.second;
		}
	}

	showBoard[pos.first][pos.second].second = 108;

	for (int i = 0; i < roles.size(); i++) {
		pos = roles[i]->getPos();
		showBoard[pos.first][pos.second].first = icon;
	}

	// print out
	int marginUp = cameraY - cameraHeight / 2;
	int marginDown = cameraY + cameraHeight / 2;
	int marginLeft = cameraX - cameraWidth / 2;
	int marginRight = cameraX + cameraWidth / 2;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	for (int row = 0; row < cameraHeight + 2; row += 1) {
		setCursor(row, 0);
		std::cout << "|";

		for (int col = marginLeft; col < marginRight; col += 1)
		{
			if (row == 0 || row == cameraHeight + 1) {
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

void GameManager::outputInformation(std::vector<std::string>& information)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int width = cameraWidth;

	for (int row = 0; row < cameraHeight + 2; row += 1)
	{
		setCursor(row, width + 1);
		std::cout << "|";

		for (int col = 1; col < windowWidth - width - 1; col += 1)
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
		setCursor(row, width + 2);

		if (row > 0 && row < cameraHeight + 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

void GameManager::outputPlayerBoard(std::vector<std::string>& information, bool* playerList)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int playerPointer = 0;
	for (; !playerList[playerPointer] && playerPointer < int(PLAYER::INVALID); playerPointer += 1) {}

	for (int row = cameraHeight + 1; row < windowHeight; row += 1)
	{
		setCursor(row, windowWidth / 3 * playerPointer + 5);
		std::cout << "|";
    
		for (int col = 0; col < windowWidth / 4; col += 1)
		{
			std::cout << ((row == cameraHeight || row == windowHeight - 1) ? "-" : " ");
		}
    
		std::cout << "|";
		
		setCursor(row, windowWidth / 3 * playerPointer + 6);
		if (row > cameraHeight + 1 && row < windowHeight && row - cameraHeight - 2 < information.size())
		{
			std::cout << information[row - cameraHeight - 2];
		}
	}
}

bool GameManager::canSee(std::pair<int, int> current, std::pair<int, int> answer, std::vector<std::vector<std::pair<char, int>>>& showBoard)
{
	while (!(current.first == answer.first && current.second == answer.second))
	{
		current.first += (current.first < answer.first);
		current.first -= (current.first > answer.first);
		current.second += (current.second < answer.second);
		current.second -= (current.second > answer.second);

		if (gameBoard[current.first][current.second].getCanPass() == false)
		{
			return false;
		}
	}
	return true;
}

void GameManager::setCameraToCurrentRole() {
	cameraX = currentRole->getPos().second;
	cameraY = currentRole->getPos().first;

	if (cameraX < cameraWidth / 2) {
		cameraX = cameraWidth / 2;
	}

	if (cameraX > mapWidth - cameraWidth / 2) {
		cameraX = mapWidth - cameraWidth / 2;
	}

	if (cameraY < cameraHeight / 2) {
		cameraY = cameraHeight / 2;
	}

	if (cameraY > mapHeight - cameraHeight / 2) {
		cameraY = mapHeight - cameraHeight / 2;
	}

}

void GameManager::setInformation() {
	std::vector<std::string> information;

	switch (gameStatus) {
		case GAME_STATUS::MAP:
			information = normalInformation();
			break;
		case GAME_STATUS::BACKPACK:
			information = backpackInformation();
			break;
	}

	outputInformation(information);
}

std::vector<std::string> GameManager::normalInformation() {
	vector<string> information;
	information.push_back("Map height: " + to_string(mapHeight));
	information.push_back("Map width: " + to_string(mapWidth));
	information.push_back("Camera height: " + to_string(cameraHeight));
	information.push_back("Camera width: " + to_string(cameraWidth));
	information.push_back("Camera X: " + to_string(cameraX));
	information.push_back("Camera Y: " + to_string(cameraY));
	information.push_back("Current Role X: " + to_string(currentRole->getPos().second));
	information.push_back("Current Role Y: " + to_string(currentRole->getPos().first));
	information.push_back("------------------------------------------");
	information.push_back("Input 'i' to open backpack");
	information.push_back("Input 1,2,3 Display the player status");
	return information;
}

std::vector<std::string> GameManager::backpackInformation() {
	vector<string> information;
	information.push_back("Bag (Page:" + to_string(bag.getCurPage()) + "/" + to_string(bag.getMaxPage()) + ")");

	for (int i = (bag.getCurPage() - 1) * 8; i < bag.getCurPage() * 8; i++) {
		if (i >= bag.getInventorySize()) {
			information.push_back(" ");
			continue;
		}

		if (bag.getCurIndex() == i) {
			information.push_back("-> " + bag.getItemName(i) + ": " + to_string(bag.getItemAmount(i)));
		}
		else {
			information.push_back("   " + bag.getItemName(i) + ": " + to_string(bag.getItemAmount(i)));
		}
	}

	information.push_back(" "); // seperate by 1 line
	information.push_back("___________Item Description__________");
	information.push_back("To be countinue");

	return information;
}

void setPlayerInformation(std::vector<std::string>& information, bool* playerList)
{

}

void GameManager::ouptutPlayerInformationP()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int playerPointer = 0;
	for (; !playerList[playerPointer] && playerPointer < int(PLAYER::INVALID); playerPointer += 1) {}

	for (int row = cameraHeight; row < windowHeight; row += 1)
	{
		setCursor(row, cameraWidth / 3 * playerPointer);
		std::cout << (row == cameraHeight || row == windowHeight - 1 ? "*" : "|");
		for (int col = 0; col < cameraWidth / 4; col += 1)
		{
			std::cout << ((row == cameraHeight || row == windowHeight - 1) ? "-" : " ");
		}
		std::cout << (row == cameraHeight || row == windowHeight - 1 ? "*" : "|");

		setCursor(row, cameraWidth / 3 * playerPointer + 2);
		if (row >= cameraHeight && row < windowHeight && row - cameraHeight < playerInformation[playerPointer].size())
		{
			std::cout << playerInformation[playerPointer][row - cameraHeight];
		}
	}
}

bool GameManager::isPositionValid(int y, int x) {
	if (y > (mapHeight - 1) || x > (mapWidth - 1) || y < 0 || x < 0)
	{
		return false;
	}

	return (gameBoard[y][x].getCanPass());
}

