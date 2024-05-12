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
			gameBoard[row][col].setIcon((col % 10 == 9) ? '.' : '#');
		}
	}

	//set 3 roles position
	roles[0]->setPos(25, 70);
	roles[1]->setPos(25, 72);
	roles[2]->setPos(27, 70);

	//set current role
	currentRole = roles[0];

	//set status
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
	std::string icon = currentRole->getIcon();
	std::pair<int, int> pos = currentRole->getPos();

	setCameraToCurrentRole();

	//set up show board, it has char and color
	std::vector<std::vector<std::pair<std::string, int>>> showBoard(mapHeight, std::vector<std::pair<std::string, int>>(mapWidth, std::pair<std::string, int>(".", 96)));
	for (int row = 0; row < mapHeight; row += 1)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			if (pow(pos.first - row, 2) + pow(pos.second - col, 2) < pow(10, 2))
			{
				showBoard[row][col].second = (gameBoard[row][col].getIcon() == '#' ? 136 : 96);
			}
			else
			{
				showBoard[row][col].second = 119;
			}
		}
	}

	canSee(pos.first, pos.second, showBoard);

	showBoard[pos.first][pos.second].first = icon;
	showBoard[pos.first][pos.second].second = 108;

	//print out
	int marginUp = cameraY - cameraHeight / 2;
	int marginDown = cameraY + cameraHeight / 2;
	int marginLeft = cameraX - cameraWidth / 2;
	int marginRight = cameraX + cameraWidth / 2;
	for (int row = marginUp; row < marginDown; row += 1)
	{
		setCursor(row, 0);
		std::cout << "|";
		for (int col = marginLeft; col < marginRight; col += 1)
		{
			if (row == marginUp || row == marginDown - 1)
			{
				std::cout << "-";
			}
			else
			{
				setColor(showBoard[row][col].second);
				std::cout << showBoard[row][col].first;
				setColor();
			}
		}
		std::cout << "|";
	}
}

void GameManager::outputInformation(std::vector<std::string>& information)
{
	int height = cameraHeight;
	int width = cameraWidth;

	for (int row = 0; row < height; row += 1)
	{
		setCursor(row, width);
		std::cout << "|";
		for (int col = 1; col < cameraWidth - width - 1; col += 1)
		{
			if (row == 0 || row == height - 1)
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
		if (row > 0 && row < height - 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

void GameManager::outputPlayerBoard(std::vector<std::string>& information, bool* playerList)
{
	int height = std::floor(cameraHeight * CAMERA_HEIGHT_RATE);
	int width = std::floor(cameraWidth * CAMERA_WIDTH_RATE);

	int playerPointer = 0;
	for (; !playerList[playerPointer] && playerPointer < int(PLAYER::INVALID); playerPointer += 1) {}

	for (int row = 0; row < cameraHeight - height; row += 1)
	{
		setCursor(height + row, cameraWidth / 3 * playerPointer);
		std::cout << "|";
		for (int col = 0; col < cameraWidth / 5; col += 1)
		{
			if (row == 0 || row == cameraHeight - height - 1)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "|";
		setCursor(height + row, cameraWidth / 3 * playerPointer + 2);
		if (row > 0 && row < cameraWidth / 5 - 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
		}
	}
}

void GameManager::canSee(int currentY, int currentX, std::vector<std::vector<std::pair<std::string, int>>>& showBoard)
{
	for (int row = 0; row <= 20; row += 1)
	{
		for (int col = 0; col <= 20; col += 1)
		{
			int tempY, tempX;
			int y = currentY - 10 + row;
			int x = currentX - 10 + col;
			tempY = y;
			tempX = x;

			if (y > (mapHeight - 1) || x > (mapWidth - 1) || y < 0 || x < 0)
			{
				continue;
			}

			while (!(y == currentY && x == currentX))
			{
				if (x < currentX)
				{
					x += 1;
				}
				if (x > currentX)
				{
					x -= 1;
				}
				if (y < currentY)
				{
					y += 1;
				}
				if (y > currentY)
				{
					y -= 1;
				}

				if (gameBoard[y][x].getIcon() == '#')
				{
					showBoard[tempY][tempX].second = 119;
					break;
				}
			}
		}
	}
}

void GameManager::setCameraToCurrentRole() {
	cameraX = currentRole->getPos().second;
	cameraY = currentRole->getPos().first;

	if (cameraX < cameraWidth / 2) cameraX = cameraWidth / 2;
	if (cameraX > mapWidth - cameraWidth / 2) cameraX = mapWidth - cameraWidth / 2;
	if (cameraY < cameraHeight / 2) cameraY = cameraHeight / 2;
	if (cameraY > mapHeight - cameraHeight / 2) cameraY = mapHeight - cameraHeight / 2;

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
	information.push_back("Camera height: " + to_string(GameManager::cameraHeight));
	information.push_back("Camera width: " + to_string(GameManager::cameraWidth));
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

bool GameManager::isPositionValid(int y, int x) {
	if (y > (mapHeight - 1) || x > (mapWidth - 1) || y < 0 || x < 0)
	{
		return false;
	}

	return (gameBoard[y][x].getIcon() == '.');
}

