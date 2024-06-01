#include "Rect.h"
#include "Object.h"
#include "Entity.h"

// Intent: Construct a Rect object with default visibility, passability, and no contained object
// Pre: None
// Post: Constructs a Rect object with isVisible set to false, canPass set to true, and object set to NULL
Rect::Rect()
{
	this->beSelect = false;
	this->isVisible = false;
	this->canPass = true;
	this->object = NULL;
	die = 0;
}

// Intent: Get the icon and color code representing the Rect's appearance
// Pre: None
// Post: Returns a pair consisting of the icon character and its associated color code
std::pair<char, int> Rect::getIcon()
{
	if (beSelect)
	{
		char ret;
		if (isVisible == false)
		{
			ret = ' ';
		}
		else if (canPass == false)
		{
			ret = '#';
		}
		else if (object == NULL)
		{
			ret = '.';
		}
		else {
			ret = object->getIcon();
		}
		return std::pair<char, int>(ret, 192);
	}
	else if (isVisible == false) 
	{
		// If not visible, return space character and a color code representing fog
		return std::pair<char, int>(' ', 119); // in war of fog
	}
	else if (canPass == false) 
	{
		// If not passable, return '#' character and a color code representing a wall
		return std::pair<char, int>('#', 136); // wall
	}
	else if (object == NULL) 
	{
		// If no object present, return '.' character and a color code representing a path
		return std::pair<char, int>('.', 96); // path
	}
	else 
	{
		// If an object is present, return its icon and a default color code
		if (beSelect)
		{
			return std::pair<char, int>(object->getIcon(), 192);
		}
		return std::pair<char, int>(object->getIcon(), 96); // have something
	}
}

// Intent: Set the visibility status of the Rect
// Pre: None
// Post: Sets the visibility status of the Rect to the specified value
void Rect::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

// Intent: Set the passability status of the Rect
// Pre: None
// Post: Sets the passability status of the Rect to the specified value
void Rect::setCanPass(bool b) 
{
	this->canPass = b;
}

// Intent: Set the object contained in the Rect
// Pre: None
// Post: Sets the object contained in the Rect to the specified object
void Rect::setObject(Object* o) 
{
	// Delete the previous object if present
	if (object != NULL) 
	{
		//delete(object);
	}
	object = o;
}

// Intent: Get the visibility status of the Rect
// Pre: None
// Post: Returns the visibility status of the Rect
bool Rect::getIsVisible()
{
	return this->isVisible;
}

// Intent: Get the passability status of the Rect
// Pre: None
// Post: Returns the passability status of the Rect
bool Rect::getCanPass() 
{
	return this->canPass;
}

// Intent: Get the object contained in the Rect
// Pre: None
// Post: Returns the object contained in the Rect
Object* Rect::getObject() 
{
	return this->object;
}

void Rect::setBeSelect(bool b)
{
	this->beSelect = b;
}

bool  Rect::getBeSelect()
{
	return this->beSelect;
}