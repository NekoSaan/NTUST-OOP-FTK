#pragma once
#include <iostream>
#include "Point.h"
using namespace std;

class Character
{
public:
	Character();

	Character(char icon, Point pos);

	void setPos(Point pos);

	Point getPos();

	char getStatus();

	void characterMove(Point pos, Point mapSize, Point& currentPoint, Point consoleSize);

private:
	char status;
	char icon;

	Point pos;
};

Character::Character()
{
	this->icon = 'H';
	this->status = 'H';

	this->pos = Point{ 0,0 };
}

Character::Character(char icon, Point pos)
{
	this->icon = icon;
	this->status = status;

	this->pos = pos;
}

void Character::setPos(Point pos)
{
	this->pos = pos;
}

Point Character::getPos()
{
	return this->pos;
}

char Character::getStatus()
{
	return this->status;
}

void Character::characterMove(Point pos, Point mapSize, Point& currentPoint, Point consoleSize)
{
	Point tempPos = (this->pos) + pos;

	if (tempPos.y < 0 || tempPos.x < 0 || tempPos.x >= mapSize.x || tempPos.y >= mapSize.x)
	{
		return void();
	}

	if (pos.y == -1)
	{
		if (currentPoint.y > consoleSize.y / 2)
		{
		}
		else
		{
			if (tempPos.y > consoleSize.y / 2)
			{
				currentPoint.y -= 1;
			}
		}

		this->pos = tempPos;
		return void();
	}

	if (pos.x == -1)
	{
		if (currentPoint.x > consoleSize.x / 3)
		{
		}
		else
		{
			if (tempPos.x > consoleSize.x / 3)
			{
				currentPoint.x -= 1;
			}
		}

		this->pos = tempPos;
		return void();
	}

	if (pos.y == 1)
	{
		if (currentPoint.y > (mapSize.y - (consoleSize.y / 2)))
		{
		}
		else
		{
			if (tempPos.y > consoleSize.y / 2)
			{
				currentPoint.y += 1;
			}
		}
		this->pos = tempPos;
		return void();
	}


	if (pos.x == 1)
	{
		if (currentPoint.x > (mapSize.x - (consoleSize.x / 3)))
		{
		}
		else
		{
			if (tempPos.x > consoleSize.x / 3)
			{
				currentPoint.x += 1;
			}
		}
		this->pos = tempPos;
		return void();
	}
}