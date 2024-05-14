#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "Role.h"

class Object;
class Rect;

enum class PLAYER
{
	PLAYER1 = 0,
	PLAYER2 = 1,
	PLAYER3 = 2,
	INVALID,
};

enum class GAME_STATUS {
	MAP, //on map
	COMBAT, // fight with enemy
	BACKPACK, //open backpack
	INTERACTIVE //interact with object on map
};

class GameManager
{
private:
	void setCameraToCurrentRole();
	void setColor(int color = 7);
	void setCursor(int y, int x);

	std::vector<std::string> normalInformation();
	std::vector<std::string> backpackInformation();
	std::vector<std::string> playerInformation[3];

	bool playerList[3] = { false };

	static std::vector<Role*> roles;
	static Role* currentRole;

	static GameManager* instance;
	GameManager(); //init roles 

public:
	static GameManager* getInstance();

	static const float CAMERA_HEIGHT_RATE; //camera height in window height rate
	static const float CAMERA_WIDTH_RATE; //camera width in window width rate

	static int mapHeight;
	static int mapWidth;
	static int cameraHeight;
	static int cameraWidth;
	static int cameraX;
	static int cameraY;

	static GAME_STATUS gameStatus;
	static std::vector<std::vector<Rect>> gameBoard;
	
	static bool isPositionValid(int y, int x);

	Role* getRole(int i);
	Role* getCurrentRole();

	void setMap();

	void outputGameBoard();

	//set information by informationStatus, then call outputInformation()
	void setInformation();
	//input string array, print information on screen left, I think it is useful, so I put it in public
	void outputInformation(std::vector<std::string>& information);

	// Set plyaer information
	void setPlayerInformation(std::vector<std::string>& information, bool* playerList);
	void ouptutPlayerInformationP();

	void outputPlayerBoard(std::vector<std::string>& information, bool* playerList);
	bool canSee(std::pair<int, int> current, std::pair<int, int> answer, std::vector<std::vector<std::pair<char, int>>>& showBoard);
};
