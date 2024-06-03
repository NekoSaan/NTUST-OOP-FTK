#include "Object.h"
#include "GameManager.h"

// Initialize static member variables
const string Object::TAG_SHOP = "Shop";
const string Object::TAG_ENEMY = "Enemy";
const string Object::TAG_EVENT = "Event";
const string Object::TAG_TENT = "Tent";

// Intent: Construct an Object with default icon and position
// Pre: None
// Post: Constructs an Object with default icon 'H' and position (0, 0)
Object::Object()
{
	// Set default icon to 'H'
	this->icon = 'H';

	// Set default position to (0, 0)
	this->y = 0;
	this->x = 0;
}

// Intent: Construct an Object with specified icon and position
// Pre: None
// Post: Constructs an Object with specified icon, y, and x position
Object::Object(char icon, int y, int x)
{
	// Set icon, y, and x to specified values
	this->icon = icon;
	this->y = y;
	this->x = x;
}

// Intent: Set the position of the object to specified coordinates
// Pre: None
// Post: Sets the position of the object to the specified (y, x) coordinates
void Object::setPos(int y, int x)
{
	this->y = y;
	this->x = x;
}

// Intent: Get the position of the object
// Pre: None
// Post: Returns a pair representing the (y, x) coordinates of the object's position
std::pair<int, int> Object::getPos()
{
	return std::pair<int, int>(this->y, this->x);
}

// Intent: Get the icon of the object
// Pre: None
// Post: Returns the icon representing the object
char Object::getIcon()
{
	return this->icon;
}

// Intent: Get the tag of the object
// Pre: None
// Post: Returns the tag representing the type of the object
std::string Object::getTag() 
{
	return tag;
}

// Intent: Start the active state of the object
// Pre: None
// Post: Sets the game status to interactive and sets the current interactive object
void Object::startActive() 
{
	GameManager::gameStatus = GAME_STATUS::INTERACTIVE;
	GameManager::getInstance()->setInteractiveObject(this);
}

// Intent: Exit the active state of the object
// Pre: None
// Post: Sets the game status back to map and clears the current interactive object
void Object::exitActive(Role* role)
{
	GameManager::gameStatus = GAME_STATUS::MAP;
	GameManager::getInstance()->setInteractiveObject(NULL);
	exitActiveEvent(role);
}

void Object::exitActiveEvent(Role* role) {

}
