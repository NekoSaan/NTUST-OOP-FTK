#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "Items.h"

class Weapon : public Item
{
public:
	int pAttack;						// Physical attack attribute
	int mAttack;						// Magical attack attribute
	int hitRate;						// Hit rate attribute
	char type;						    // Type of equipment (physical or magical)
	std::string activeSkill = "NULL";	// Active skill associated with the weapon

	// Constructor for Weapon class
	Weapon(std::string, ITEMID);

	// Get the physical attack attribute of the weapon
	int getPAttack(void);

	// Get the magical attack attribute of the weapon
	int getMAttack(void);

	// Get hit rate
	int getHitRate(void);

	// Get the type of the weapon (physical or magical)
	char getType(void);

	// Get the active skill of the weapon
	std::string getActiveSkill(void);

	void use(Role*) override;
};

#endif _WEAPON_H_
