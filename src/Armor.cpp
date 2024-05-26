#include "Armor.h"
#include "Role.h"
#include "Backpack.h"

Armor::Armor(std::string tag, ITEMID id)
	: Item::Item(tag, id) 
{
	vitality = 0;
	speed = 0;
	pDefense = 0;
	mDefense = 0;
	type = 'p';

	switch (id) {
		case ITEMID::WoodenShield:
			pDefense = 10;
			activeSkill = "Provoke";
			break;
		case ITEMID::PlateArmor:
			pDefense = 20;
			speed = -10;
			activeSkill = "Fortify";
			break;
		case ITEMID::LeatherArmor:
			pDefense = 5;
			activeSkill = "Fortify";
			break;
		case ITEMID::Robe:
			mDefense = 10;
			type = 'm';
		case ITEMID::LaurelWreath:
			type = 'm';
			break;
		default:
			break;
	}
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

void Armor::use(Role* role) {
	// Because when we equip, we use the same pointer.
	if (role->armor->getTag() == "Weapon") {
		role->armor->incAmount();
	}
	else {
		// Not equipped.
		delete role->armor;
		role->weapon = nullptr;
	}

	role->armor = this;
}