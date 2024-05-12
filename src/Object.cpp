#include "Object.h"
#include "GameManager.h"

Object::Object()
{
	this->icon = "H";

	this->y = 0;
	this->x = 0;
}

Object::Object(std::string tag, int y, int x)
{
	this->icon = tag;

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

std::string Object::getIcon()
{
	return this->icon;
}

std::string Object::getTag() {
	return tag;
}

