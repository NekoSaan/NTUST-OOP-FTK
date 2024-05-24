#include "Weapon.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Construct a Weapon object with specified tag and ID
// Pre: None
// Post: Constructs a Weapon object with specified tag and ID, and initializes its attributes to default values
Weapon::Weapon(std::string tag, ITEMID id) : Item::Item(tag, id)
{
	// Initialize attributes to default values
	pAttack = 0;
	mAttack = 0;
	hitRate = 0;
	type = 'p';

	// accroding to id to assign
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

// Intent: Get hir rate attribute of the weapon
// Pre: None
// Post: Returns the hir rate attribute of the weapon
int Weapon::getHitRate(void) {
	return hitRate;
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

void Weapon::use(Role* role) {
	if (role->weapon->getTag() == "Weapon") {
		
	}
	else {
		delete role->weapon;
		role->weapon = nullptr;
	}

	role->weapon = this;
}