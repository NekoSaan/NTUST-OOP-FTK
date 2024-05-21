#include "Rect.h"
#include "Object.h"
#include "Entity.h"

Rect::Rect()
{
	this->isVisible = false;
	this->canPass = true;

	this->object = NULL;
}

std::pair<char, int> Rect::getIcon()
{
	if (isVisible == false) {
		return std::pair<char, int>(' ', 119); //in war of fog
	}
	else if (canPass == false) {
		return std::pair<char, int>('#', 136); // wall
	}
	else if (object == NULL) {
		return std::pair<char, int>('.', 96); //path
	}
	else {
		return std::pair<char, int>(object->getIcon(), 96); //have something
	}
}

void Rect::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

void Rect::setCanPass(bool b) {
	this->canPass = b;
}

void Rect::setObject(Object* o) {
	if (object != NULL) {
		delete(object);
	}
	object = o;
}

bool Rect::getIsVisible()
{
	return this->isVisible;
}

bool Rect::getCanPass() {
	return this->canPass;
}

Object* Rect::getObject() {
	return this->object;
}
