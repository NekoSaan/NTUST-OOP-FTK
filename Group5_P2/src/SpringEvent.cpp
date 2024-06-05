#include "SpringEvent.h"
#include "dice.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Constructs a SpringEvent object with default values.
// Pre: None.
// Post: Initializes a SpringEvent object with default values for usedFocus, chosenIndex, diceNum, hasActive, icon, and tag. It also updates the description of the event.
SpringEvent::SpringEvent() {
	this->usedFocus = 0;
	this->chosenIndex = 0;
	this->diceNum = 4;
	this->hasActive = false;
	this->icon = '?';
	this->tag = TAG_EVENT;

	//init description
	updateDescription();
}

// Intent: Update the description of the SpringEvent based on its current state.
// Pre: None.
// Post: Updates the description vector with appropriate messages depending on whether the event has an active effect and the result of the dice roll.
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
		// The dice result 4 description add 20 hp
		description.clear();
		description.push_back("So sweet.");
		description.push_back("4 You heel 20 HP!");
	}
	else if (diceResult == 3) {
		// The dice result 3 description add 10 hp
		description.clear();
		description.push_back("So sweet.");
		description.push_back("3 You heel 10 HP!");
	}
	else if (diceResult == 2) {
		// The dice result 2 description add 5 hp
		description.clear();
		description.push_back("Nice.");
		description.push_back("2 You heel 5 HP!");
	}
	else if (diceResult == 1) {
		// The dice result 1 description nothing
		description.clear();
		description.push_back("Just normal water.");
		description.push_back("1 Nothing happend");
	}
	else if (diceResult == 0) {
		// The dice result 0 damage
		description.clear();
		description.push_back("It is posion!");
		description.push_back("0 You get 10 damage!");
	}
}

// Intent: Execute the event's action and modify the role's attributes accordingly.
// Pre: role must point to a valid Role object.
// Post: Performs a dice roll to determine the event outcome, adjusts the role's focus, and applies the corresponding effect based on the dice result.
void SpringEvent::startEvent(Role* role)
{
	diceResult = dice(usedFocus, diceNum, 60);
	role->setFocus(role->getFocus() - usedFocus);
	switch (diceResult) {
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