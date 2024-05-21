#include "ChestEvent.h"
#include "dice.h"
#include "Role.h"
#include "Backpack.h"

ChestEvent::ChestEvent() {
	this->usedFocus = 0;
	this->chosenIndex = 0;
	this->diceNum = 3;
	this->hasActive = false;
	this->icon = '?';
	this->tag = TAG_EVENT;
	this->description = "Do you want to open the chest?\n3 get $100(12.5%)\n2 get $20(37.5%)\n1 get $5(37.5%)\n0 10 damage(12.5%)";
}

//Event virtual function
void ChestEvent::startEvent(Role* role) {
	int n = dice(usedFocus, diceNum, 50);
	role->setFocus(role->getFocus() - usedFocus);
	switch (n) {
	case 3:
		bag.earnMoney(100);
		break;
	case 2:
		bag.earnMoney(20);
		break;
	case 1:
		bag.earnMoney(5);
		break;
	case 0:
		role->setHp(role->getHp() - 10);
	}
}