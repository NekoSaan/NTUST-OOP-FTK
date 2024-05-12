#pragma once
#include <windows.h>
#include <vector>
#include "Rect.h"
#include "Object.h"

extern const float CAMERAHEIGHTRATE;
extern const float CAMERAWIDTHRATE;

extern int mapHeight;
extern int mapWidth;

extern int cameraHeight;
extern int cameraWidth;

extern int cameraX;
extern int cameraY;

extern std::vector<std::vector<Rect>> gameBoard;

enum class PLAYER
{
	PLAYER1 = 0,
	PLAYER2 = 1,
	PLAYER3 = 2,
	INVALID,
};

class GameManager
{
public:
	void setColor(int color = 7);

	void setCursor(int y, int x);

	void setMap();

	void outputGameBoard(std::string icon, std::pair<int, int> pos);

	void outputInformation(std::vector<std::string>& information);

	void outputPlayerBoard(std::vector<std::string>& information, bool* playerList);

	void GameManager::canSee(int currentY, int currentX, std::vector<std::vector<std::pair<std::string, int>>>& showBoard);
};
