#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Point.h"
#include "Role.h"

using namespace std;

class Object {
public:
	Object();

	Object(string icon, Point pos);

	void setPos(Point pos);

	Point getPos();

	string getTag();

	void ObjectMove(Point pos);

    //virtual void startActive() = 0; //tell game need to display choose screen
    //virtual void active(Role* role) = 0;
    //virtual void chooseActiveUP() = 0; 
    //virtual void chooseActiveDown() = 0;
    //virtual vector<string> getAllChoose() = 0; // return all choose's name, you can use it to display

private:
	string tag;

	Point pos;
};

Object::Object()
{
	this->tag = "H";

	this->pos = Point{ 0,0 };
}

Object::Object(string tag, Point pos)
{
	this->tag = tag;

	this->pos = pos;
}

void Object::setPos(Point pos)
{
	this->pos = pos;
}

Point Object::getPos()
{
	return this->pos;
}

string Object::getTag()
{
	return this->tag;
}

void Object::ObjectMove(Point pos)
{
	Point tempPos = (this->pos) + pos;

	if (tempPos.y < 0 || tempPos.x < 0 || tempPos.x >= mapWidth || tempPos.y >= mapHeight)
	{
		return void();
	}

	if (pos.y == -1)
	{
		if (cameraHeight / 2 <= tempPos.y && tempPos.y <= mapHeight - (cameraHeight / 2))
		{
			cameraY -= 1;
		}

		this->pos = tempPos;
		return void();
	}

	if (pos.x == -1)
	{
		if (cameraWidth / 3 <= tempPos.x && tempPos.x <= mapWidth - (cameraWidth / 3))
		{
			cameraX -= 1;
		}

		this->pos = tempPos;
		return void();
	}

	if (pos.y == 1)
	{
		if (cameraHeight / 2 <= tempPos.y && tempPos.y <= mapHeight - (cameraHeight / 2))
		{
			cameraY += 1;
		}

		this->pos = tempPos;
		return void();
	}


	if (pos.x == 1)
	{
		if (cameraWidth / 3 <= tempPos.x && tempPos.x <= mapWidth - (cameraWidth / 3))
		{
			cameraX += 1;
		}

		this->pos = tempPos;
		return void();
	}
}

#endif // _OBJECT_H_