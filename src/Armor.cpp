#include "Armor.h"
#include "Role.h"

Armor::Armor(std::string tag, ITEMID id)
	: Item::Item(tag, id) 
{
	vitality = 0;
	speed = 0;
	pDefense = 0;
	mDefense = 0;
	type = 'p';
}

// Intent: Get the vitality attribute of the weapon
// Pre: None
// Post: Returns the vitality attribute of the weapon
int Armor::getVitality(void)
{
	return vitality;
}

// Intent: Get the speed attribute of the weapon
// Pre: None
// Post: Returns the speed attribute of the weapon
int Armor::getSpeed(void)
{
	return speed;
}


// Intent: Get the physical defense attribute of the weapon
// Pre: None
// Post: Returns the physical defense attribute of the weapon
int Armor::getPDefense(void)
{
	return pDefense;
}

// Intent: Get the magical defense attribute of the weapon
// Pre: None
// Post: Returns the magical defense attribute of the weapon
int Armor::getMDefense(void)
{
	return mDefense;
}

// Intent: Get the type of the weapon (physical or magical)
// Pre: None
// Post: Returns the type of the weapon
char Armor::getType(void)
{
	return type;
}

// Intent: Get the active skill of the weapon
// Pre: None
// Post: Returns the active skill of the weapon
std::string Armor::getActiveSkill(void)
{
	return activeSkill;
}

void use(Role* role) {

}