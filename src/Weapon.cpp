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

	Weapon(std::string tag, ITEMID id) : Item::Item(tag, id) {
		vitality = 0;
		speed = 0;
		pAttack = 0;
		mAttack = 0;
		pDefense = 0;
		mDefense = 0;
		type = 'p';
	}

	int getVitality(void) { return vitality; }
	int getSpeed(void) { return speed; }
	int getPAttack(void) { return pAttack; }
	int getMAttack(void) { return mAttack; }
	int getPDefense(void) { return pDefense; }
	int getMDefense(void) { return mDefense; }
	char getType(void) { return type; }
	std::string getActiveSkill(void) { return activeSkill; }
};

#endif // _WEAPON_H_
