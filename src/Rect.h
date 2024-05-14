#ifndef _RECT_H_
#define _RECT_H_
#include <utility>

class Object;

class Rect
{
public:
	Rect();

	std::pair<char, int> getIcon();

	void setIsVisible(bool visible);
	void setCanPass(bool b);
	void setObject(Object* o);

	bool getIsVisible();
	bool getCanPass();
	Object* getObject();

private:
	bool isVisible;
	bool canPass;

	Object* object;
};
#endif // _RECT_H_
