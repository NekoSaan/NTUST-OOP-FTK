#include "Role.h"
#include "GameManager.h"
#include "Rect.h"

// Intent: Move the role to a new position on the game board and trigger any interactions with objects on the new position
// Pre: Parameters y and x represent the change in position (delta y, delta x) from the current position
// Post: Updates the role's position on the game board and triggers any interactions with objects on the new position
void Role::move(int y, int x)
{
	// Calculate the new position
	int tempPosY = this->y + y;
	int tempPosX = this->x + x;

	// Check if the new position is valid
	if (!GameManager::isPositionValid(tempPosY, tempPosX))
	{
		return void(); // If the new position is not valid, exit the function
	}

	// Update the role's position
	setPos(tempPosY, tempPosX);

	// Check if there is an object on the rect
	GameManager* gameManager = GameManager::getInstance();
	Object* objectOnRect = gameManager->gameBoard[tempPosY][tempPosX].getObject();

	// If an object is present on the rect, trigger its active state
	if (objectOnRect != NULL) 
	{
		objectOnRect->startActive();
	}
}

void Role::gainHealth(int healHp) {
	hp = min(hp + healHp, vitality);
}

void Role::gainFocus(int restoreN) {
	focus = min(focus + restoreN, maxFocus);
}

void Role::active(Role* role) 
{
}

void Role::chooseActiveUP() 
{
}

void Role::chooseActiveDown() 
{
}

// Intent: Get all possible choices for the role's actions
// Pre: None
// Post: Returns a vector of strings representing all possible choices for the role's actions
vector<string> Role::getAllChoose() 
{
	return vector<string>();
}

// Intent: Get the index of the chosen action
// Pre: None
// Post: Returns the index of the chosen action
int Role::getChosenIndex() 
{
	return 0;
}

vector<string> Role::getDescription() {
	vector<string> description;
	description.push_back("This is a role.");
	description.push_back("Actually, you should not read this.");
	return description;
}
