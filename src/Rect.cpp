#include "Rect.h"

Rect::Rect()
{
	this->isVisible = false;
	this->canPass = true;

	this->icon = '.';
}

void Rect::setIcon(char i)
{
	this->icon = i;
}

char Rect::getIcon()
{
	return icon;
}

void Rect::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

bool Rect::getIsVisible()
{
	return this->isVisible;
}