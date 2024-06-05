#include "Role.h"
#include "Rect.h"
#include "Backpack.h"
#include "TeleportScroll.h"
#include "GameManager.h"

// Intent: Constructs a TeleportScrool object with the provided tag.
// Pre: None.
// Post: Initializes a TeleportScrool object with the given tag and the item ID of TeleportScroll.
TeleportScrool::TeleportScrool(std::string tag) : Item::Item(tag, ITEMID::TeleportScroll) {};

// Intent: Use the TeleportScroll object to teleport the role.
// Pre: role must point to a valid Role object.
// Post: Allows the role to choose a destination within its visible range on the game board and teleport to that location.
void TeleportScrool::use(Role* role) {

	// Pointer to the game manager instance
	GameManager* gameManager;
	gameManager = GameManager::getInstance();
	int originalY = role->getPos().first;
	int originalX = role->getPos().second;
	int y = role->getPos().first;
	int x = role->getPos().second;

	for (char input = ' '; input != '\r';) {
		gameManager->gameBoard[y][x].setBeSelect(true);
		char icon = role->getIcon();
		std::pair<int, int> pos = role->getPos();

		gameManager->cameraX = x;
		gameManager->cameraY = y;

		// The X edge check whether touch the upper edge
		if (gameManager->cameraX < gameManager->cameraWidth / 2) {
			gameManager->cameraX = gameManager->cameraWidth / 2;
		}

		// The X edge check whether touch the down edge
		if (gameManager->cameraX > gameManager->mapWidth - gameManager->cameraWidth / 2) {
			gameManager->cameraX = gameManager->mapWidth - gameManager->cameraWidth / 2;
		}

		// The Y edge check whether touch the right edge
		if (gameManager->cameraY < gameManager->cameraHeight / 2) {
			gameManager->cameraY = gameManager->cameraHeight / 2;
		}

		// The Y edge check whether touch the left edge
		if (gameManager->cameraY > gameManager->mapHeight - gameManager->cameraHeight / 2) {
			gameManager->cameraY = gameManager->mapHeight - gameManager->cameraHeight / 2;
		}

		// set up show board, 2D vector has pair, it has char and color
		std::vector<std::vector<std::pair<char, int>>> showBoard(gameManager->mapHeight, std::vector<std::pair<char, int>>(gameManager->mapWidth, std::pair<char, int>('.', 96)));

		for (int row = 0; row < gameManager->mapHeight; row += 1) {
			for (int col = 0; col < gameManager->mapWidth; col += 1) {
				// If the gameboard get isn't visible
				if (!gameManager->gameBoard[row][col].getIsVisible()) {
					// The range in player can see range
					if (pow(pos.first - row, 2) + pow(pos.second - col, 2) < pow(10, 2)) {
						// If the Position without the block and see direction
						if (gameManager->canSee(std::pair<int, int>(row, col), pos, showBoard)) {
							gameManager->gameBoard[row][col].setIsVisible(true);
						}
					}
				}

				// set icon
				std::pair<char, int> icon = gameManager->gameBoard[row][col].getIcon();
				showBoard[row][col].first = icon.first;
				showBoard[row][col].second = icon.second;
			}
		}

		gameManager->outputShowBoard(showBoard, icon);

		input = _getch();
		gameManager->gameBoard[y][x].setBeSelect(false);

		int yAdd = 0, xAdd = 0;
		switch (input) {
		case 'W':
		case 'w':
			yAdd -= 1;
			break;
		case 'S':
		case 's':
			yAdd += 1;
			break;
		case 'A':
		case 'a':
			xAdd -= 1;
			break;
		case 'D':
		case 'd':
			xAdd += 1;
			break;
		}

		if (y + yAdd >= gameManager->mapHeight || y + yAdd < 0 || x + xAdd >= gameManager->mapWidth || x + xAdd < 0) {
			continue;
		}

		if (gameManager->gameBoard[y + yAdd][x + xAdd].getIsVisible() && gameManager->gameBoard[y + yAdd][x + xAdd].getIcon().first == '.') {
			y += yAdd;
			x += xAdd;
			gameManager->gameBoard[y][x].setBeSelect(true);
		}

	}
	gameManager->gameBoard[y][x].setBeSelect(false);
	role->setPos(y, x);
}