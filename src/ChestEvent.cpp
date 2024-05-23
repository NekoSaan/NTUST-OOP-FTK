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
}

vector<string> ChestEvent::getDescription() {
	vector<string> description;
	string probability = "";
	description.push_back("Do you want to open the chest ?");
	description.push_back("3 get $100(" + formatProbability(getExpectProbability(usedFocus, diceNum, 3, 50)) + "%)");
	description.push_back("2 get $20(" + formatProbability(getExpectProbability(usedFocus, diceNum, 2, 50)) + "%)");
	description.push_back("1 get $5(" + formatProbability(getExpectProbability(usedFocus, diceNum, 1, 50)) + "%)");
	description.push_back("0 10 damage(" + formatProbability(getExpectProbability(usedFocus, diceNum, 0, 50)) + "%)");
	description.push_back("Used focus: " + to_string(usedFocus));
	return description;
}

//Event virtual function
void ChestEvent::startEvent(Role* role) 
{
	int n = dice(usedFocus, diceNum, 50);
	role->setFocus(role->getFocus() - usedFocus);
	switch (n) 
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
}