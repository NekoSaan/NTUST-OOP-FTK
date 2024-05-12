#include "Role.h"
#include "GameManager.h"

void Role::move(int y, int x)
{
	int tempPosY = this->y + y;
	int tempPosX = this->x + x;

	if (!GameManager::isPositionValid(tempPosY, tempPosX))
	{
		return void();
	}

	setPos(tempPosY, tempPosX);
}