#pragma once

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