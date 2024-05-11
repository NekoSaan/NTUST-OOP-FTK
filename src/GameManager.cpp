#include "GameManager.h"

const float CAMERAHEIGHTRATE = 0.55;
const float CAMERAWIDTHRATE = 0.66;

int mapHeight = 50;
int mapWidth = 140;

int cameraHeight = 0;
int cameraWidth = 0;

int cameraX = 0;
int cameraY = 0;

std::vector<std::vector<Rect>> gameBoard(mapHeight, std::vector<Rect>(mapWidth));

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
			gameBoard[row][col].setStatus((col % 10 == 9) ? '.' : '#');
		}
	}

	//character.setPos(std::pair<int,int>( int(cameraHeight * CAMERAHEIGHTRATE / 2), int(cameraWidth * CAMERAWIDTHRATE / 2) ));
}

void GameManager::outputGameBoard(std::string icon, std::pair<int, int> pos)
{
	std::vector<std::vector<std::pair<std::string, int>>> showBoard(mapHeight, std::vector<std::pair<std::string, int>>(mapWidth, std::pair<std::string, int>(".", 96)));
	for (int row = 0; row < mapHeight; row += 1)
	{
		for (int col = 0; col < mapWidth; col += 1)
		{
			if (pow(pos.first - row, 2) + pow(pos.second - col, 2) < pow(10, 2))
			{
				showBoard[row][col].second = (gameBoard[row][col].getStatus() == '#' ? 136 : 96);
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

	for (int row = 0; row < std::floor(cameraHeight * CAMERAHEIGHTRATE); row += 1)
	{
		setCursor(row, 0);
		std::cout << "|";
		for (int col = 0; col < std::floor(cameraWidth * CAMERAWIDTHRATE); col += 1)
		{
			if (row == 0 || row == std::floor(cameraHeight * CAMERAHEIGHTRATE) - 1)
			{
				std::cout << "-";
			}
			else
			{
				setColor(showBoard[row + cameraY][col + cameraX].second);
				std::cout << showBoard[row + cameraY][col + cameraX].first;
				setColor();
			}
		}
		std::cout << "|";
	}
}

void GameManager::outputInformation(std::vector<std::string>& information)
{
	int height = std::floor(cameraHeight * CAMERAHEIGHTRATE);
	int width = std::floor(cameraWidth * CAMERAWIDTHRATE);

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
	int height = std::floor(cameraHeight * CAMERAHEIGHTRATE);
	int width = std::floor(cameraWidth * CAMERAWIDTHRATE);

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

				if (gameBoard[y][x].getStatus() == '#')
				{
					showBoard[tempY][tempX].second = 119;
					break;
				}
			}
		}
	}
}