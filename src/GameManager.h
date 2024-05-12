#pragma once
#include <windows.h>
#include <vector>
#include "Rect.h"
#include "Object.h"
#include "Role.h"

enum class PLAYER
{
	PLAYER1 = 0,
	PLAYER2 = 1,
	PLAYER3 = 2,
	INVALID,
};

enum GAME_STATUS {
	MAP,
	COMBAT
};

enum INFORMATION_STATUS {
	NORMAL,
	BAG,
	SHOP
};

class GameManager
{
public:
	static const float CAMERA_HEIGHT_RATE; //camera height in window height rate
	static const float CAMERA_WIDTH_RATE; //camera width in window width rate

	static int mapHeight;
	static int mapWidth;
	static int cameraHeight;
	static int cameraWidth;
	static int cameraX;
	static int cameraY;

	static int gameStatus;
	static int informationStatus;

	static std::vector<std::vector<Rect>> gameBoard;
	static std::vector<Role*> roles;

	static Role* currentRole;

	GameManager(); //init roles

	void setColor(int color = 7);
	void setCursor(int y, int x);

	void setMap();

	void outputGameBoard(std::string icon, std::pair<int, int> pos);
	void outputInformation(std::vector<std::string>& information);
	void outputPlayerBoard(std::vector<std::string>& information, bool* playerList);
	void canSee(int currentY, int currentX, std::vector<std::vector<std::pair<std::string, int>>>& showBoard);
};
