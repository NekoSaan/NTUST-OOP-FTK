#include "GameManager.h"
#include <iostream>
#include "Rect.h"
#include "Object.h"
#include "Backpack.h"
#include "Role.h"
#include "Shop.h"

const float GameManager::CAMERA_HEIGHT_RATE = 0.55;
const float GameManager::CAMERA_WIDTH_RATE = 0.66;

int GameManager::mapHeight = 50;
int GameManager::mapWidth = 140;
int GameManager::windowHeight = 0;
int GameManager::windowWidth = 0;
int GameManager::cameraHeight = 0;
int GameManager::cameraWidth = 0;
int GameManager::cameraX = 0;
int GameManager::cameraY = 0;

GAME_STATUS GameManager::gameStatus;

std::vector<std::vector<Rect>> GameManager::gameBoard(mapHeight, std::vector<Rect>(mapWidth));

std::vector<Role*> GameManager::roles;
Role* GameManager::currentRole;
Object* GameManager::interactiveObject;

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
	interactiveObject = NULL;
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

Object* GameManager::getInteractiveObject() {
	return interactiveObject;
}
void GameManager::setInteractiveObject(Object* o) {
	interactiveObject = o;
}

void GameManager::battleScreen()
{
	system("CLS");
	setEnemyInformation();
	setPlayerInformation();
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

	std::vector<std::string> mode;
	mode.push_back("Name:");
	mode.push_back("");
	mode.push_back("   Attack");
	mode.push_back("   Escape");

	std::vector<std::string> descript;
	descript.push_back("Description:");
	descript.push_back("");
	descript.push_back("\tRoll Amount:");
	descript.push_back("\tRoll Probability:");
	descript.push_back("\tDamage Type:");
	descript.push_back("\tCool Down:");

	char input;
	int chocie = 1;
	do
	{	
		for (int i = 0; i < mode.size(); i += 1)
		{
			setCursor(windowHeight / 3 + i + 1, 3);
			cout << mode[i];
		}
		
		for (int i = 0; i < descript.size(); i += 1)
		{
			setCursor(windowHeight / 3 + i + 1, cameraX / 2);
			cout << descript[i];
		}

		input = _getch();
		switch (input)
		{
		case 'w':
			chocie = (chocie < 1 ? 1 : chocie - 1);
			break;
		case 's':
			chocie = (chocie > mode.size() ? chocie : chocie + 1);
		}
		if (chocie == 1)
		{
			mode[2] = "->" + mode[2].substr(2);
			mode[3] = "  " + mode[3].substr(2);
		}
		else
		{
			mode[2] = "  " + mode[2].substr(2);
			mode[3] = "->" + mode[3].substr(2);
		}
	} while (input != '\r');


	// Escpae
	if (chocie == 1)
	{

	}
	// Attack
	else
	{

	}
}

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

	// print out rolled map
	int marginUp = cameraY - cameraHeight / 2;
	int marginDown = cameraY + cameraHeight / 2;
	int marginLeft = cameraX - cameraWidth / 2;
	int marginRight = cameraX + cameraWidth / 2;

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
	for (int row = 0; row < cameraHeight + 2; row += 1)
	{
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

		if (row > 0 && row < cameraHeight + 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
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
	case GAME_STATUS::INTERACTIVE:
		information = interactiveInformation();
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

	string seperateLine = "";

	for (int i = 1; i < windowWidth - cameraWidth - 6; i++) {
		if (i == (windowWidth - cameraWidth - 6) / 2) {
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

	information.push_back(" "); // Seperate by 1 line
	string seperateLine = "";

	for (int i = 1; i < windowWidth - cameraWidth - 16; i++) {
		if (i == (windowWidth - cameraWidth - 16) / 2) {
			seperateLine += "Item Description";
			continue;
		}

		seperateLine += "_";
	}

	information.push_back(seperateLine);
	information.push_back("To be countinue");

	return information;
}

std::vector<std::string> GameManager::interactiveInformation() {
	vector<string> choose = interactiveObject->getAllChoose();
	vector<string> information;

	// one page display 8 choice
	int currentPage = interactiveObject->getChosenIndex() / 8;
	int maxPage = choose.size() / 8;
	int pageStartIndex = currentPage * 8;

	//information about object
	information.push_back(interactiveObject->getTag() + " (Page: " + to_string(currentPage + 1) + "/" + to_string(maxPage + 1) + ")");
	information.push_back("Your money: $" + to_string(bag.getMoney()));
	information.push_back("------------");

	// what you can do with object
	for (int i = pageStartIndex; i < pageStartIndex + 8 && i < choose.size(); i++) {
		if (i == interactiveObject->getChosenIndex()) {
			information.push_back("-> " + choose[i]);
		}
		else {
			information.push_back("   " + choose[i]);
		}
	}

	return information;
}

void GameManager::setPlayerInformation(void)
{
	for (int i = 0; i < roles.size(); i++) {
		vector<string> info;

		info.push_back("Name: Player" + to_string(i));
		info.push_back("HP: " + to_string(roles[i]->getHp()) + "/" + to_string(roles[i]->getVitality())
			+ ", Focus: " + to_string(roles[i]->getFocus()) + "/" + to_string(roles[i]->getMaxFocus()));
		info.push_back("Physical ATK: " + to_string(roles[i]->getPAttack())
			+ ", Physical DEF: " + to_string(roles[i]->getPDefense()));
		info.push_back("Magical ATK: " + to_string(roles[i]->getMAttack())
			+ ", Magical DEF: " + to_string(roles[i]->getMDefense()));
		info.push_back("Speed: " + to_string(roles[i]->getSpeed())
			+ ", HitRate: " + to_string(roles[i]->getHitRate()));
		info.push_back("Weapon: " + roles[i]->getWeaponName());
		info.push_back("Armor: ");
		info.push_back("Accessory: ");
		info.push_back("Buff: ");

		outputPlayerBoard(info, i);
	}
}

void GameManager::outputPlayerBoard(std::vector<std::string>& information, int playerPointer)
{
	for (int row = windowHeight / 3 * 2; row < windowHeight; row += 1)
	{
		setCursor(row, windowWidth / 3 * playerPointer + 2);
		std::cout << "|";

		for (int col = 0; col < windowWidth / 4 + 5; col += 1)
		{
			std::cout << ((row == windowHeight / 3 * 2 || row == windowHeight - 1) ? "-" : " ");
		}

		std::cout << "|";

		setCursor(row, windowWidth / 3 * playerPointer + 3);
		if (row > windowHeight / 3 * 2 && row < windowHeight - 1 && row - (windowHeight / 3 * 2) - 1 < information.size())
		{
			std::cout << information[row - (windowHeight / 3 * 2) - 1];
		}
	}
}

void GameManager::setEnemyInformation(void)
{
	for (int i = 0; i < roles.size(); i++) 
	{
		vector<string> info;
		info.push_back("Name: Enemy" + to_string(i));
		info.push_back("HP: " + to_string(roles[i]->getHp()) + "/" + to_string(roles[i]->getVitality())
			+ ", Focus: " + to_string(roles[i]->getFocus()) + "/" + to_string(roles[i]->getMaxFocus()));
		info.push_back("Physical ATK: " + to_string(roles[i]->getPAttack())
			+ ", Physical DEF: " + to_string(roles[i]->getPDefense()));
		info.push_back("Magical ATK: " + to_string(roles[i]->getMAttack())
			+ ", Magical DEF: " + to_string(roles[i]->getMDefense()));
		info.push_back("Speed: " + to_string(roles[i]->getSpeed())
			+ ", HitRate: " + to_string(roles[i]->getHitRate()));
		info.push_back("Weapon: " + roles[i]->getWeaponName());
		info.push_back("Armor: ");
		info.push_back("Accessory: ");
		info.push_back("Buff: ");

		outputEnemyBoard(info, i);
	}
}

void GameManager::outputEnemyBoard(std::vector<std::string>& information, int playerPointer)
{
	for (int row = 0; row < windowHeight / 3; row += 1)
	{
		setCursor(row, windowWidth / 3 * playerPointer + 2);
		std::cout << "|";

		for (int col = 0; col < windowWidth / 4 + 5; col += 1)
		{
			std::cout << ((row == 0 || row == windowHeight / 3 - 1) ? "-" : " ");
		}

		std::cout << "|";

		setCursor(row, windowWidth / 3 * playerPointer + 3);
		if (row > 0 && row < windowHeight / 3 - 1 && row - 1 < information.size())
		{
			std::cout << information[row - 1];
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

