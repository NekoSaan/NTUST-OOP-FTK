#include "SpringEvent.h"
#include "dice.h"
#include "Role.h"
#include "Backpack.h"

SpringEvent::SpringEvent()
{
	this->usedFocus = 0;
	this->chosenIndex = 0;
	this->diceNum = 4;
	this->hasActive = false;
	this->icon = '?';
	this->tag = TAG_EVENT;

	//init description
	updateDescription();
}

void SpringEvent::updateDescription() {
	if (hasActive == false) {
		description.clear();
		this->description.push_back("Do you want to drink this spring?");
		this->description.push_back("hit 4 heel 20 HP (" + formatProbability(getExpectProbability(usedFocus, diceNum, 4, 60)) + ")");
		this->description.push_back("hit 3 heel 10 HP (" + formatProbability(getExpectProbability(usedFocus, diceNum, 3, 60)) + ")");
		this->description.push_back("hit 2 heel 5 HP (" + formatProbability(getExpectProbability(usedFocus, diceNum, 2, 60)) + ")");
		this->description.push_back("hit 1 nothing (" + formatProbability(getExpectProbability(usedFocus, diceNum, 1, 60)) + ")");
		this->description.push_back("hit 0 get 10 damage (" + formatProbability(getExpectProbability(usedFocus, diceNum, 0, 60)) + ")");
		this->description.push_back("Used focus: " + to_string(usedFocus));
	}
	else if (diceResult == 4) {
		description.clear();
		description.push_back("So sweet.");
		description.push_back("4 You heel 20 HP!");
	}
	else if (diceResult == 3) {
		description.clear();
		description.push_back("So sweet.");
		description.push_back("3 You heel 10 HP!");
	}
	else if (diceResult == 2) {
		description.clear();
		description.push_back("Nice.");
		description.push_back("2 You heel 5 HP!");
	}
	else if (diceResult == 1) {
		description.clear();
		description.push_back("Just normal water.");
		description.push_back("1 Nothing happend");
	}
	else if (diceResult == 0) {
		description.clear();
		description.push_back("It is posion!");
		description.push_back("0 You get 10 damage!");
	}
}

//Event virtual function
void SpringEvent::startEvent(Role* role)
{
	diceResult = dice(usedFocus, diceNum, 60);
	role->setFocus(role->getFocus() - usedFocus);
	switch (diceResult)
	{
	case 4:
		role->gainHealth(20);
		break;
	case 3:
		role->gainHealth(10);
		break;
	case 2:
		role->gainHealth(5);
		break;
	case 1:
		break;
	case 0:
		role->setHp(role->getHp() - 10);
	}
	hasActive = true;
}