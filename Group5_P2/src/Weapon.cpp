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
	dp = 1;
	type = 'p';
	cd = 0;

	switch (id) {
	case ITEMID::WoodenSword:
		pAttack = 5;
		hitRate = 10;
		dp = 3;
		activeSkill = "SpeedUp";
		break;
	case ITEMID::Hammer:
		pAttack = 15;
		hitRate = -15;
		dp = 4;
		activeSkill = "Provoke";
		passiveSkill = "Hammer-Splash";
		break;
	case ITEMID::GiantHammer:
		pAttack = 20;
		hitRate = -15;
		dp = 5;
		passiveSkill = "Hammer-Splash";
		break;
	case ITEMID::MagicWand:
		mAttack = 10;
		type = 'm';
		dp = 3;
		activeSkill = "Heal";
		break;
	case ITEMID::RitualSword:
		mAttack = 15;
		type = 'm';
		activeSkill = "Shock - Blast";
		passiveSkill = "Destroy";
		break;
	default:
		// empty, invalid, bug.
		break;
	}
}

// Intent: Get the physical attack attribute of the weapon
// Pre: None
// Post: Returns the physical attack attribute of the weapon
int Weapon::getPAttack(void) {
	return pAttack; 
}

// Intent: Get the magical attack attribute of the weapon
// Pre: None
// Post: Returns the magical attack attribute of the weapon
int Weapon::getMAttack(void) {
	return mAttack; 
}

// Intent: Get hit rate attribute of the weapon
// Pre: None
// Post: Returns the hit rate attribute of the weapon
int Weapon::getHitRate(void) { 
	return hitRate; 
}

// Intent: Get dice pool attribute of the weapon
// Pre: None
// Post: Returns the dice pool attribute of the weapon
int Weapon::getDP(void) { 
	return dp; 
}

// Intent: Get the type of the weapon (physical or magical)
// Pre: None
// Post: Returns the type of the weapon
char Weapon::getType(void) { 
	return type; 
}

// Intent: Get the active skill of the weapon
// Pre: None
// Post: Returns the active skill of the weapon
std::string Weapon::getActiveSkill(void) { 
	return activeSkill; 
}

// Intent: Use the Weapon object for the specified role.
// Pre: role must point to a valid Role object.
// Post: The role's weapon is updated to point to this Weapon object. If the role already has a weapon equipped, its amount is increased; otherwise, the previous weapon is deleted and set to nullptr.
void Weapon::use(Role* role) {
	// Because when we equip, we use the same pointer.
	if (role->weapon->getTag() == "Weapon") {
		role->weapon->incAmount();
	}
	else {
		// Not equipped.
		delete role->weapon;
		role->weapon = nullptr;
	}

	role->weapon = this;
}

// Intent: Get the passive skill associated with this Weapon object.
// Pre: None.
// Post: Returns the passive skill name.
std::string Weapon::getPassiveSkill(void)
{
	return passiveSkill;
}

// Intent: Set the cooldown time for this Weapon object.
// Pre: CD must be a non-negative integer.
// Post: Sets the cooldown time for the weapon.
void  Weapon::setCD(int CD) {
	cd = CD;
}

// Intent: Get the cooldown time of this Weapon object.
// Pre: None.
// Post: Returns the cooldown time of the weapon.
int Weapon::getCD() {
	return cd;
}