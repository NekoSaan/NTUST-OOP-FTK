#include "Rect.h"

Rect::Rect()
{
	this->isVisible = true;
	this->canPass = true;

	this->status = '.';
}

void Rect::setStatus(char status)
{
	this->status = status;
}

char Rect::getStatus()
{
	return status;
}