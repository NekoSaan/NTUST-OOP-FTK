#include "Event.h"
#include "Role.h"

Event::Event() {
	this->usedFocus = 0;
	this->chosenIndex = 0;
	this->diceNum = 3;
	this->hasActive = false;
	this->icon = '?';
	this->tag = TAG_EVENT;
	this->description = "Random thing will happen.";
}

void Event::active(Role* role) {
	switch (chosenIndex) {
	case 0:
		startEvent(role);
		break;
	case 1:
		usedFocus++;
		if (usedFocus > diceNum) usedFocus = diceNum;
		if (usedFocus > role->getFocus()) usedFocus = role->getFocus();
		break;
	case 2:
		usedFocus--;
		if (usedFocus < 0) usedFocus = 0;
		break;
	case 3:
		exitActive();
	}
}

void Event::chooseActiveUP() {
	chosenIndex--;

	if (chosenIndex < 0) {
		chosenIndex = 3;
	}
}

void Event::chooseActiveDown() {
	chosenIndex++;

	if (chosenIndex > 3) {
		chosenIndex = 0;
	}
}

vector<string> Event::getAllChoose() {
	vector<string> choose;
	choose.push_back("Do it!");
	choose.push_back("Increase focus");
	choose.push_back("Decrease focus");
	choose.push_back("Go back");
	return choose;
}

int Event::getChosenIndex() {
	return chosenIndex;
}