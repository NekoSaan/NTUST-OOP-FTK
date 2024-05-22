#include "Weapon.h"

// Intent: Construct a Weapon object with specified tag and ID
// Pre: None
// Post: Constructs a Weapon object with specified tag and ID, and initializes its attributes to default values
Weapon::Weapon(std::string tag, ITEMID id)
	: Item::Item(tag, id)
{
	// Initialize attributes to default values
	vitality = 0;
	speed = 0;
	pAttack = 0;
	mAttack = 0;
	pDefense = 0;
	mDefense = 0;
	type = 'p';
}

// Intent: Get the vitality attribute of the weapon
// Pre: None
// Post: Returns the vitality attribute of the weapon
int Weapon::getVitality(void) 
{
	return vitality; 
}

// Intent: Get the speed attribute of the weapon
// Pre: None
// Post: Returns the speed attribute of the weapon
int Weapon::getSpeed(void) 
{
	return speed; 
}

// Intent: Get the physical attack attribute of the weapon
// Pre: None
// Post: Returns the physical attack attribute of the weapon
int Weapon::getPAttack(void) 
{
	return pAttack; 
}

// Intent: Get the magical attack attribute of the weapon
// Pre: None
// Post: Returns the magical attack attribute of the weapon
int Weapon::getMAttack(void)
{
	return mAttack; 
}

// Intent: Get the physical defense attribute of the weapon
// Pre: None
// Post: Returns the physical defense attribute of the weapon
int Weapon::getPDefense(void) 
{
	return pDefense;
}

// Intent: Get the magical defense attribute of the weapon
// Pre: None
// Post: Returns the magical defense attribute of the weapon
int Weapon::getMDefense(void)
{
	return mDefense;
}

// Intent: Get the type of the weapon (physical or magical)
// Pre: None
// Post: Returns the type of the weapon
char Weapon::getType(void) 
{
	return type; 
}

// Intent: Get the active skill of the weapon
// Pre: None
// Post: Returns the active skill of the weapon
std::string Weapon::getActiveSkill(void) 
{
	return activeSkill; 
}
