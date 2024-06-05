#include "Armor.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Construct a armor with tag & id.
// Pre: tag & id of armor.
// Post: A new armor item be created in game.
// \param tag: tag of item, for recgonize type of items.
// \param id: id of item, to recgonize which item it is.
Armor::Armor(std::string tag, ITEMID id) : Item::Item(tag, id) {
	// init all attribute to 0, in case of getting nullptr
	vitality = 0;
	speed = 0;
	pDefense = 0;
	mDefense = 0;
	type = 'p';

	// Assign real equipment attribute by recgonize id
	switch (id) {
		case ITEMID::WoodenShield:
			pDefense = 10;
			break;
		case ITEMID::PlateArmor:
			pDefense = 20;
			speed = -10;
			passiveSkill = "Fortify";
			break;
		case ITEMID::LeatherArmor:
			pDefense = 5;
			passiveSkill = "Fortify";
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
std::string Armor::getPassiveSkill(void)
{
	return passiveSkill;
}

// Intent: Let role equip the equipment.
// Pre: Target role who want to equip.
// Post: The target role equipped the item/equipment.
// \param role*: Pointer of role.
void Armor::use(Role* role) {
	// Because when we equip, we use the same pointer.
	if (role->armor->getTag() == "Armor") {
		// so we only need to increase amount of it.
		role->armor->incAmount();
	}
	else {
		// Not equipped, delete the `empty equipment`
		delete role->armor;
		role->armor = nullptr;
	}

	role->armor = this;
}