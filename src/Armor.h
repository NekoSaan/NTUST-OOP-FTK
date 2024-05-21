#ifndef _ARMOR_H_
#define _ARMOR_H_
#include "Items.h"

class Armor : public Item{
private:
	int vitality;		// hp
	int speed;			// speed
	int pDefense;		// physical defense
	int mDefense;		// magical defense
	char type;			// type of equipment
	std::string activeSkill = "NULL";

public:
	Armor(std::string tag, ITEMID id) : Item::Item(tag, id) {
		vitality = 0;
		speed = 0;
		pDefense = 0;
		mDefense = 0;
		type = 'p';
	}

	int getVitality(void) { return vitality; }
	int getSpeed(void) { return speed; }
	int getPDefense(void) { return pDefense; }
	int getMDefense(void) { return mDefense; }
	char getType(void) { return type; }
	std::string getActiveSkill(void) { return activeSkill; }
};

#endif // _ARMOR_H_
