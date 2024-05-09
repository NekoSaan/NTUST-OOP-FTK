#pragma once
#include "Point.h"

class Rect
{
public:
	Rect();

	void setStatus(char status);

	char getStatus();

private:
	bool isVisible;
	bool canPass;

	char status;
};

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