#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "Items.h"

class Weapon : public Item {
public:
	int vitality;		// hp
	int speed;			// speed
	int pAttack;		// physical attack
	int mAttack;		// magical attack
	int pDefense;		// physical defense
	int mDefense;		// magical defense
	char type;			// type of equipment
	std::string activeSkill = "NULL";
	std::string weaponName;

	Weapon(std::string tag, ITEMID id);

	int getVitality(void);
	int getSpeed(void);
	int getPAttack(void);
	int getMAttack(void);
	int getPDefense(void);
	int getMDefense(void);
	char getType(void);
	std::string getActiveSkill(void);
};

#endif // _WEAPON_H_
