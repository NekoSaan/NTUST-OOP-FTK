#ifndef _RECT_H_
#define _RECT_H_
#include "Point.h"

class Rect {
public:
	Rect();

	void setStatus(char status);

	char getStatus();

	char getIcon();

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

#endif // _RECT_H_
