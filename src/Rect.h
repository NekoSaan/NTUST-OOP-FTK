#ifndef _RECT_H_
#define _RECT_H_

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
#endif // _RECT_H_
