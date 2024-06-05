#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Items.h"

class Weapon : public Item
{
private:
	int pAttack;						// Physical attack attribute
	int mAttack;						// Magical attack attribute
	int hitRate;						// Hit rate attribute
	int dp;								// Abbreviation of `dice pool`
	char type;						    // Type of equipment (physical or magical)
	std::string activeSkill = "NULL";	// Active skill associated with the weapon
	std::string passiveSkill = "NULL";	// Passive skill associated with the weapon
	int cd;								// Weapon cd
public:
	// Constructor for Weapon class
	Weapon(std::string, ITEMID);
	
	// Get the physical attack attribute of the weapon
	int getPAttack(void);

	// Get the magical attack attribute of the weapon
	int getMAttack(void);

	// Get hit rate
	int getHitRate(void);

	// Get dice pool
	int getDP(void);

	// Get the type of the weapon (physical or magical)
	char getType(void);

	// Get the active skill of the weapon
	std::string getActiveSkill(void);

	// Get the active skill of the weapon
	std::string getPassiveSkill(void);
	void setCD(int CD);
	int getCD();
	
	// Use weapon
	void use(Role*) override;
};

#endif // _WEAPON_H_