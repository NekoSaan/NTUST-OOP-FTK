#include "Object.h"
#include "GameManager.h"

const string Object::TAG_SHOP = "Shop";
const string Object::TAG_ENEMY = "Enemy";
const string Object::TAG_EVENT = "Random Event";

Object::Object()
{
	this->icon = 'H';

	this->y = 0;
	this->x = 0;
}

Object::Object(char icon, int y, int x)
{
	this->icon = icon;

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

char Object::getIcon()
{
	return this->icon;
}

std::string Object::getTag() {
	return tag;
}

std::string Object::getDescription() {
	return description;
}

void Object::startActive() {
	GameManager::gameStatus = GAME_STATUS::INTERACTIVE;
	GameManager::getInstance()->setInteractiveObject(this);
}

void Object::exitActive() {
	GameManager::gameStatus = GAME_STATUS::MAP;
	GameManager::getInstance()->setInteractiveObject(NULL);
}

