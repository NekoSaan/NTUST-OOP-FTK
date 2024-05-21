#include "Weapon.h"

Weapon::Weapon(std::string tag, ITEMID id) 
	: Item::Item(tag, id)
{
	vitality = 0;
	speed = 0;
	pAttack = 0;
	mAttack = 0;
	pDefense = 0;
	mDefense = 0;
	type = 'p';
}

int Weapon::getVitality(void) { return vitality; }
int Weapon::getSpeed(void) { return speed; }
int Weapon::getPAttack(void) { return pAttack; }
int Weapon::getMAttack(void) { return mAttack; }
int Weapon::getPDefense(void) { return pDefense; }
int Weapon::getMDefense(void) { return mDefense; }
char Weapon::getType(void) { return type; }
std::string Weapon::getActiveSkill(void) { return activeSkill; }