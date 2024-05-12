#include "Rect.h"

Rect::Rect()
{
	this->isVisible = true;
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