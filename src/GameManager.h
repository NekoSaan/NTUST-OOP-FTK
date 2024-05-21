#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>	
#include "Role.h"

class Object;
class Rect;

enum class PLAYER
{
	PLAYER1 = 0,
	PLAYER2,
	PLAYER3,
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

	// Input string array, print information on screen left
	void outputInformation(std::vector<std::string>& information);

	std::vector<std::string> normalInformation();
	std::vector<std::string> backpackInformation();
	std::vector<std::string> interactiveInformation();
	std::vector<std::string> playerInformation[3];

	bool playerList[3] = { false };

	static std::vector<Role*> roles;
	static Role* currentRole;
	static Object* interactiveObject;

	static GameManager* instance;
	GameManager(); // init roles 

public:
	static GameManager* getInstance();

	static const float CAMERA_HEIGHT_RATE; // camera height in window height rate
	static const float CAMERA_WIDTH_RATE; // camera width in window width rate

	static int mapHeight;
	static int mapWidth;
	static int windowHeight;
	static int windowWidth;
	static int cameraHeight;
	static int cameraWidth;
	static int cameraX;
	static int cameraY;

	static GAME_STATUS gameStatus;
	static std::vector<std::vector<Rect>> gameBoard;
	
	static bool isPositionValid(int y, int x);

	Role* getRole(int i);
	Role* getCurrentRole();
	Object* getInteractiveObject();
	void setInteractiveObject(Object* o);

	void setMap();

	void battleScreen();

	void outputGameBoard();

	// Set information by informationStatus, then call outputInformation()
	void setInformation();
	
	// Set plyaer information
	void setPlayerInformation(void);
	void outputPlayerBoard(std::vector<std::string>&, int);

	// Set enemy information
	void setEnemyInformation(void);
	void outputEnemyBoard(std::vector<std::string>&, int);

	bool canSee(std::pair<int, int> current, std::pair<int, int> answer, std::vector<std::vector<std::pair<char, int>>>& showBoard);
};

#endif // _GAMEMANAGER_H_
