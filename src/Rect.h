#ifndef _RECT_H_
#define _RECT_H_

class Rect
{
public:
	Rect();

	void setIcon(char i);

	char getIcon();

	void setIsVisible(bool visible);

	bool getIsVisible();

private:
	bool isVisible;
	bool canPass;

	char icon;
};
#endif // _RECT_H_
