#include "Role.h"
#include "GameManager.h"
#include "Rect.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "Dice.h"

Role::Role(void) : Entity::Entity() {

};

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

int selectTarget(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	char c = getch();
	int targetIndex = c - '0';  // Convert char to integer
	if (targetIndex < 0 || targetIndex >= enemy.size()) {
		std::cout << "Invalid target. Please try again." << std::endl;
		// Recurse until valid input is received
		return selectTarget(role, enemy);
	}
	return targetIndex;
}

// Intent: Select an action for the entity based on user input
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Selects an action for the entity based on user input
int Role::selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy) {
	GameManager* gameManager = GameManager::getInstance();
	int selectedOption = 0;
	int numOptions = 3;  // Number of options in the menu

	while (true) {
		gameManager->battleScreen(role, enemy, { "" }, { " selct your Action\n" });

		// Display menu with highlighted selected option
		for (int i = 0; i < numOptions; ++i) {
			if (i == selectedOption) {
				std::cout << "-> ";
			}
			else {
				std::cout << "   ";
			}

			switch (i) {
			case 0:
				std::cout << "Normal Attack\n";
				break;
			case 1:
				std::cout << weapon->getActiveSkill() << std::endl;
				break;
			case 2:
				std::cout << "Flee\n";
				break;
			}
		}

		char input = getch();

		// Handle arrow keys for navigation
		if (input == 'w' && selectedOption > 0) {
			selectedOption--;
		}
		else if (input == 's' && selectedOption < numOptions - 1) {
			selectedOption++;
		}
		else if (input == '\r') {  // '\r' is Enter key
			switch (selectedOption) {
			case 0:
				normalAttack(role, enemy);
				break;
			case 1:
				skillAttack(role, enemy);
				break;
			case 2:
				if (Flee() == 1) {
					return 1;
				}
				break;
			}
			break;  // Exit loop after selection made
		}	
	}
	return 0;
}

// Intent: Perform a normal attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a normal attack against an enemy entity
void Role::normalAttack(std::vector<Entity*> role, std::vector<Entity*> enemy) {
	GameManager* gameManager = GameManager::getInstance();
	gameManager->battleScreen(role, enemy, { "" }, { "select target(input number)" });

	int targetIndex = selectTarget(role, enemy);
	gameManager->battleScreen(role, enemy, { "" }, { "" });

	if (weapon->getType() == 'p') {
		int n = useFocus(1);
		int absorption = enemy[targetIndex]->getPDefense() / (getPDefense() + 50);
		int attack = getPAttack() * dice(n, 1, getHitRate());
		enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() - attack * (1 - absorption));

	}
	else {
		int n = useFocus(1);
		int absorption = enemy[targetIndex]->getMDefense() / (getMDefense() + 50);
		int attack = getMAttack() * dice(n, 1, getHitRate());
		enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() - attack * (1 - absorption));
	}
}

// Intent: Perform a skill attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a skill attack against an enemy entity
void Role::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy)
{
	GameManager* gameManager = GameManager::getInstance();
	gameManager->battleScreen(role, enemy, { "" }, { "select target(input number)" });
	
	if (weapon->getActiveSkill() == "Provoke")
	{
		int HitRate = getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed();
		int targetIndex = selectTarget(role, enemy);
		int n = useFocus(1);

		if (dice(n, 1, HitRate) == 1)
		{
			enemy[targetIndex]->giveBuff("Angry", 3);
		}
	}
	else if(weapon->getActiveSkill() == "Shock - Blast"){
		int n = useFocus(3);
		for (int i = 0; i < enemy.size(); i++) {
			int absorption = enemy[i]->getMDefense() / (getMDefense() + 50);
			int attack = getMAttack() * dice(n, 3, getHitRate()-5);
			enemy[i]->setHp(enemy[i]->getHp() - attack/2 * (1 - absorption));
		}
    }
	else if (weapon->getActiveSkill() == "Heal") {
		
		int targetIndex = selectTarget(role, role);
		int n = useFocus(2);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[targetIndex]->setHp(role[targetIndex]->getHp() + getMAttack() * 3 / 2);
		}
	}
	else if (weapon->getActiveSkill() == "SpeedUp")
	{
		int targetIndex = selectTarget(role, role);
		int n = useFocus(2);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[targetIndex]->giveBuff("SpeedUp", 3);
		}
	}	
}
