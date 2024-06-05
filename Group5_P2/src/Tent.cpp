#include "Tent.h"
#include "GameManager.h"

// Intent: Construct a Tent object with the provided rectangle.
// Pre: rect must point to a valid Rect object.
// Post: Tent object is initialized with default values for tag, icon, cooldown (cd), chosenIndex, and rect. The Tent object is also registered as an observer with the GameManager.
Tent::Tent(Rect* rect) {
	this->tag = Object::TAG_TENT;
	this->icon = 'T';
	this->cd = 3;
	this->chosenIndex = 0;
	this->rect = rect;

	GameManager::getInstance()->addObserver(this);
}

// Intent: Update the cooldown of the Tent object and remove it from the game if the cooldown reaches zero.
// Pre: None.
// Post: Decreases the cooldown of the Tent object. If the cooldown reaches zero or less, removes the Tent object from its associated rectangle and unregister it as an observer from the GameManager.
void Tent::notify() {
	cd--;
	if (cd <= 0) {
		rect->setObject(NULL);
		GameManager::getInstance()->removeObserver(this);
	}
}

// Intent: Perform the active action of the Tent object for the specified role.
// Pre: role must point to a valid Role object.
// Post: Executes different actions based on the chosenIndex of the Tent object:
void Tent::active(Role* role) {
	switch (chosenIndex) {
	case 0:
		GameManager::getInstance()->nextRole();
		exitActive(role);
		break;
	case 1:
		exitActive(role);
		break;
	}
}

// Intent: Decrease the chosenIndex of the Tent object.
// Pre: None.
// Post: Decreases the chosenIndex by 1. If the chosenIndex becomes less than 0, wraps around to 1.
void Tent::chooseActiveUP() {
	chosenIndex--;
	if (chosenIndex < 0) {
		chosenIndex = 1;
	}
}

// Intent: Increase the chosenIndex of the Tent object.
// Pre: None.
// Post: Increases the chosenIndex by 1. If the chosenIndex becomes greater than 1, wraps around to 0.
void Tent::chooseActiveDown() {
	chosenIndex++;
	if (chosenIndex > 1) {
		chosenIndex = 0;
	}
}

// Intent: Get all the available choices for the Tent object.
// Pre: None.
// Post: Returns a vector of strings containing all the available choices.
vector<string> Tent::getAllChoose() {
	vector<string> choose;
	choose.push_back("Take a break");
	choose.push_back("Go back");
	return choose;
}

// Intent: Get the current chosen index of the Tent object.
// Pre: None.
// Post: Returns the current chosen index.
int Tent::getChosenIndex() {
	return chosenIndex;
}

// Intent: Get the description of the Tent object's action.
// Pre: None.
// Post: Returns a vector of strings containing the description of the Tent object's action.
vector<string> Tent::getDescription() {
	vector<string> description;
	description.push_back("You can take a break and recover some HP and Focus");
	return description;
}