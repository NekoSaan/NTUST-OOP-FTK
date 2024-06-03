#include "Tent.h"
#include "GameManager.h"

Tent::Tent(Rect* rect) {
	this->tag = Object::TAG_TENT;
	this->icon = 'T';
	this->cd = 3;
	this->chosenIndex = 0;
	this->rect = rect;

	GameManager::getInstance()->addObserver(this);
}

void Tent::notify() {
	cd--;
	if (cd <= 0) {
		rect->setObject(NULL);
		GameManager::getInstance()->removeObserver(this);
	}
}

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

void Tent::chooseActiveUP() {
	chosenIndex--;
	if (chosenIndex < 0) {
		chosenIndex = 1;
	}
}

void Tent::chooseActiveDown() {
	chosenIndex++;
	if (chosenIndex > 1) {
		chosenIndex = 0;
	}
}

vector<string> Tent::getAllChoose() {
	vector<string> choose;
	choose.push_back("Take a break");
	choose.push_back("Go back");
	return choose;
}

int Tent::getChosenIndex() {
	return chosenIndex;
}

vector<string> Tent::getDescription() {
	vector<string> description;
	description.push_back("You can take a break and recover some HP and Focus");
	return description;
}