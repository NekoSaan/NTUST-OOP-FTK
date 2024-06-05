#include "Accessory.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Construct a accessory with tag & id.
// Pre: tag & id of accessory.
// Post: A new accessory item be created in game.
// \param tag: tag of item, for recgonize type of items.
// \param id: id of item, to recgonize which item it is.
Accessory::Accessory(std::string tag, ITEMID id) : Item::Item(tag, id) {
	// init attribute to 0
	mDefense = 0;
	speed = 0;
	maxFocus = 0;

	// Accroding to item's id to assign attribute.
	switch (id) {
		case ITEMID::HolyGrail:
			mDefense = 30;
			break;
		case ITEMID::Shoes:
			speed = 5;
			passiveSkill = "Run";
			break;
		case ITEMID::Bracelet:
			maxFocus = 1;
			break;
		default:
			break;
	}
};

// Intent: Get the magical defense attribute of the weapon
// Pre: None
// Post: Returns the magical defense attribute of the weapon
int Accessory::getMDefense(void) const { return mDefense; }

// Intent: Get the speed attribute of the weapon
// Pre: None
// Post: Returns the speed attribute of the weapon
int Accessory::getSpeed(void) const { return speed; }

// Intent: Get max focus
// Pre: None
// Post: Retunrs max focus that accessory provide
int Accessory::getMaxFocus(void) const { return maxFocus; }

// Intent: Get passive skill
// Pre: None
// Post: Return passive skill of equipment
std::string Accessory::getPassiveSkill(void) const { return passiveSkill; }

// Intent: Let role equip the equipment.
// Pre: Target role who want to equip.
// Post: The target role equipped the item/equipment.
// \param role*: Pointer of role.
void Accessory::use(Role* role) {
	// Because when we equip, we use the same pointer in backpack.
	if (role->acc->getTag() == "Accessory") {
		// so we only need to increase amount of it.
		role->acc->incAmount();
	}
	else {
		// Not equipped, delete `empty equipment`.
		delete role->acc;
		role->acc = nullptr;
	}

	role->acc = this;
}