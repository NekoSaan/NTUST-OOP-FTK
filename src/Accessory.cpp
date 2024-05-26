#include "Accessory.h"
#include "Role.h"
#include "Backpack.h"

Accessory::Accessory(std::string tag, ITEMID id) : Item::Item(tag, id) {
	// init stat
	mDefense = 0;
	speed = 0;
	maxFocus = 0;

	switch (id) {
		case ITEMID::HolyGrail:
			mDefense = 30;
			activeSkill = "Heal";
			break;
		case ITEMID::Shoes:
			speed = 5;
			activeSkill = "Run";
			break;
		case ITEMID::Bracelet:
			maxFocus = 1;
			break;
		default:
			break;
	}
};

// Intent: Get the speed attribute of the weapon
// Pre: None
// Post: Returns the speed attribute of the weapon
int Accessory::getSpeed(void)
{
	return speed;
}

// Intent: Get the magical defense attribute of the weapon
// Pre: None
// Post: Returns the magical defense attribute of the weapon
int Accessory::getMDefense(void)
{
	return mDefense;
}

// Intent: Get max focus
// Pre: None
// Post: Retunrs max focus that accessory provide
int Accessory::getMaxFocus(void) {
	return maxFocus;
}

void Accessory::use(Role* role) {
	// Because when we equip, we use the same pointer.
	if (role->acc->getTag() == "Accessory") {
		role->acc->incAmount();
	}
	else {
		// Not equipped.
		delete role->acc;
		role->acc = nullptr;
	}

	role->acc = this;
}