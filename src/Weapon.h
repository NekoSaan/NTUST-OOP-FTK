#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "Items.h"

class Weapon : public Item
{
public:
	int vitality;						// Health points (HP)
	int speed;							// Speed attribute
	int pAttack;						// Physical attack attribute
	int mAttack;						// Magical attack attribute
	int pDefense;						// Physical defense attribute
	int mDefense;						// Magical defense attribute
	char type;						    // Type of equipment (physical or magical)
	std::string activeSkill = "NULL";	// Active skill associated with the weapon
	std::string weaponName;				// Name of the weapon

	// Constructor for Weapon class
	Weapon(std::string tag, ITEMID id);

	// Get the vitality attribute of the weapon
	int getVitality(void);

	// Get the speed attribute of the weapon
	int getSpeed(void);

	// Get the physical attack attribute of the weapon
	int getPAttack(void);

	// Get the magical attack attribute of the weapon
	int getMAttack(void);

	// Get the physical defense attribute of the weapon
	int getPDefense(void);

	// Get the magical defense attribute of the weapon
	int getMDefense(void);

	// Get the type of the weapon (physical or magical)
	char getType(void);

	// Get the active skill of the weapon
	std::string getActiveSkill(void);
};

#endif _WEAPON_H_
