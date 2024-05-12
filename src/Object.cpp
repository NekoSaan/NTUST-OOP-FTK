#include"Object.h"

Object::Object()
{
	this->tag = "H";

	this->y = 0;
	this->x = 0;
}

Object::Object(std::string tag, int y, int x)
{
	this->tag = tag;

	this->y = y;
	this->x = x;
}

void Object::setPos(int y, int x)
{
	this->y = y;
	this->x = x;
}

std::pair<int, int> Object::getPos()
{
	return std::pair<int, int>(this->y, this->x);
}

std::string Object::getTag()
{
	return this->tag;
}

void Object::ObjectMove(int y, int x)
{
	int tempPosY = this->y + y;
	int tempPosX = this->x + x;
	int edgeSizeY = std::floor(cameraHeight * CAMERAHEIGHTRATE) / 2;
	int edgeSizeX = std::floor(cameraWidth * CAMERAWIDTHRATE) / 2;

	if (!isPositionValid(tempPosY, tempPosX))
	{
		return void();
	}

	if (y == -1)
	{
		if (edgeSizeY <= tempPosY && tempPosY <= mapHeight - edgeSizeY)
		{
			cameraY -= 1;
		}
		setPos(tempPosY, tempPosX);
	}

	if (x == -1)
	{
		if (edgeSizeX <= tempPosX && tempPosX <= mapWidth - edgeSizeX)
		{
			cameraX -= 1;
		}
		setPos(tempPosY, tempPosX);
	}

	if (y == 1)
	{
		if (edgeSizeY <= tempPosY && tempPosY <= mapHeight - edgeSizeY)
		{
			cameraY += 1;
		}
		setPos(tempPosY, tempPosX);
	}


	if (x == 1)
	{
		if (edgeSizeX <= tempPosX && tempPosX <= mapWidth - edgeSizeX)
		{
			cameraX += 1;
		}
		setPos(tempPosY, tempPosX);
	}
}

bool Object::isPositionValid(int y, int x)
{
	if (y > (mapHeight - 1) || x > (mapWidth - 1) || y < 0 || x < 0)
	{
		return false;
	}

	return (gameBoard[y][x].getStatus() == '.');
}