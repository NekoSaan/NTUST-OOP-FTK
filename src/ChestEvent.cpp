#include "ChestEvent.h"
#include "dice.h"
#include "Role.h"
#include "Backpack.h"

ChestEvent::ChestEvent()
{
	this->usedFocus = 0;
	this->chosenIndex = 0;
	this->diceNum = 3;
	this->hasActive = false;
	this->icon = '?';
	this->tag = TAG_EVENT;

	// init description
	this->description.push_back("Do you want to open the chest ?");
	this->description.push_back("hit 3 get $100 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 3, 50)) + ")");
	this->description.push_back("hit 2 get $20 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 2, 50)) + ")");
	this->description.push_back("hit 1 get $5 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 1, 50)) + ")");
	this->description.push_back("hit 0 get 10 damage (" + formatProbability(getExpectProbability(usedFocus, diceNum, 0, 50)) + ")");
	this->description.push_back("Used focus: " + to_string(usedFocus));
}

void ChestEvent::updateDescription() {
	if (hasActive == false) {
		description.clear();
		description.push_back("Do you want to open the chest ?");
		description.push_back("hit 3 get $100 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 3, 50)) + ")");
		description.push_back("hit 2 get $20 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 2, 50)) + ")");
		description.push_back("hit 1 get $5 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 1, 50)) + ")");
		description.push_back("hit 0 get 10 damage (" + formatProbability(getExpectProbability(usedFocus, diceNum, 0, 50)) + ")");
		description.push_back("Used focus: " + to_string(usedFocus));
	}
	else if (diceResult == 3) {
		description.clear();
		description.push_back("You open the chest.");
		description.push_back("3 You get $100!");
	}
	else if (diceResult == 2) {
		description.clear();
		description.push_back("You open the chest.");
		description.push_back("2 You get $20!");
	}
	else if (diceResult == 1) {
		description.clear();
		description.push_back("You open the chest.");
		description.push_back("1 You get $5!");
	}
	else if (diceResult == 0) {
		description.clear();
		description.push_back("It is a trap");
		description.push_back("0 You get 10 damage!");
	}
}

// Event virtual function
void ChestEvent::startEvent(Role* role)
{
	diceResult = dice(usedFocus, diceNum, 50);
	role->setFocus(role->getFocus() - usedFocus);

	switch (diceResult)
	{
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

	hasActive = true;
}