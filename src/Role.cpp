#include "Role.h"
#include "GameManager.h"
#include "Rect.h"

void Role::move(int y, int x)
{
	int tempPosY = this->y + y;
	int tempPosX = this->x + x;

	if (!GameManager::isPositionValid(tempPosY, tempPosX))
	{
		return void();
	}

	setPos(tempPosY, tempPosX);

	//check if rect has something
	GameManager* gameManager = GameManager::getInstance();
	Object* objectOnRect = gameManager->gameBoard[tempPosY][tempPosX].getObject();

	if (objectOnRect != NULL) {
		objectOnRect->startActive();
	}
}

void Role::active(Role* role) {}
void Role::chooseActiveUP() {}
void Role::chooseActiveDown() {}
vector<string> Role::getAllChoose() {
	return vector<string>();
}
int Role::getChosenIndex() {
	return 0;
}