#pragma once
#include <iostream>
#include "GameManager.h"

class Object
{
public:
	Object();

	Object(std::string icon, int y, int x);

	void setPos(int y, int x);

	std::pair<int, int> getPos();

	std::string getTag();

	void ObjectMove(int y, int x);

	bool isPositionValid(int y, int x);

private:
	std::string tag;

	int y;
	int x;
};