#include "Role.h"
#include "GameManager.h"
#include "Rect.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "Dice.h"

Role::Role(void) : Entity::Entity() {
	weapon = new Weapon("Empty", ITEMID::Invalid);
	armor = new Armor("Empty", ITEMID::Invalid);
	acc = new Accessory("Empty", ITEMID::Invalid);
};

// Intent: Move the role to a new position on the game board and trigger any interactions with objects on the new position
// Pre: Parameters y and x represent the change in position (delta y, delta x) from the current position
// Post: Updates the role's position on the game board and triggers any interactions with objects on the new position
void Role::move(int y, int x)
{
	if (movementPoint <= 0) return;
	
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
	movementPoint--;

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

void Role::setMovementPoint() {
	int maxMovementPoint = speed / 10;
	movementPoint = dice(1, maxMovementPoint, speed);
}

int Role::getMovementPoint() {
	return movementPoint;
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

int selectTarget(const std::vector<Entity*>& role, const std::vector<Entity*>& enemy) {
	GameManager* gameManager = GameManager::getInstance();

	int selectedIndex = 0;
	while (true) {
		gameManager->battleScreen(role, enemy, { "" }, { "" });
		cout << "請選擇一個目標：\n";
		for (size_t i = 0; i < enemy.size(); ++i) {
			if (i == selectedIndex) {
				cout << "> 目標 " << i + 1 << endl; // 當前選中的目標
			}
			else {
				cout << "  目標 " << i + 1 << endl;
			}
		}
		char c = _getch(); 

		if (c == 'w' || c == 'W') {
			selectedIndex = (selectedIndex - 1 + enemy.size()) % enemy.size();
		}
		else if (c == 's' || c == 'S') {
			selectedIndex = (selectedIndex + 1) % enemy.size();
		}
		else if (c == '\r') { // Enter 鍵
			return selectedIndex;
		}
	}
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
				std::cout << weapon->getActiveSkill()<<" cd:"<< weapon->getCD()<< std::endl;
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
	

	int targetIndex = selectTarget(role, enemy);
	GameManager* gameManager = GameManager::getInstance();
	gameManager->battleScreen(role, enemy, { "" }, { "" });

	if (weapon->getType() == 'p') {
		int n = useFocus(1, role, enemy);
		int absorption = enemy[targetIndex]->getPDefense() / (getPDefense() + 50);
		int attack = getPAttack() * dice(n, 1, getHitRate());
		enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() - attack * (1 - absorption));

	}
	else {
		int n = useFocus(1,role, enemy);
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
	if (weapon->getCD() > 0) {
		selectAction(role, enemy);
	}
	
	if (weapon->getActiveSkill() == "Provoke")
	{
		int HitRate = getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed();
		int targetIndex = selectTarget(role, enemy);
		int n = useFocus(1,role, enemy);

		if (dice(n, 1, HitRate) == 1)
		{
			enemy[targetIndex]->giveBuff("Angry", 3);
		}
		weapon->setCD(3);
	}
	else if(weapon->getActiveSkill() == "Shock - Blast"){
		int n = useFocus(3, role, enemy);
		for (int i = 0; i < enemy.size(); i++) {
			int absorption = enemy[i]->getMDefense() / (getMDefense() + 50);
			int attack = getMAttack() * dice(n, 3, getHitRate()-5);
			enemy[i]->setHp(enemy[i]->getHp() - attack/2 * (1 - absorption));
		}
		weapon->setCD(2);
    }
	else if (weapon->getActiveSkill() == "Heal") {
		
		int targetIndex = selectTarget(role, role);
		int n = useFocus(2,role, enemy);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[targetIndex]->setHp(role[targetIndex]->getHp() + getMAttack() * 3 / 2);
		}
		weapon->setCD(2);
	}
	else if (weapon->getActiveSkill() == "SpeedUp")
	{
		int targetIndex = selectTarget(role, role);
		int n = useFocus(2, role, enemy);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[targetIndex]->giveBuff("SpeedUp", 3);
		}
		weapon->setCD(4);
	}
	else {
		selectAction(role, enemy);
	}
}


int Role::useFocus(int MaxFocus,std::vector<Entity* > role, std::vector<Entity* > enemy) {
	vector<int> options;
	for (int i = 0; i <= MaxFocus && i <= getFocus(); ++i) {
		options.push_back(i);
	}

	int selectedIndex = 0;

	while (true) {
		GameManager* gameManager = GameManager::getInstance();
		gameManager->battleScreen(role, enemy, { "" }, { " selct your Action\n" });
		cout << "請選擇要使用的專注值：\n";
		for (size_t i = 0; i < options.size(); ++i) {
			if (i == selectedIndex) {
				cout << " > " << options[i] << " 點" << endl; // 當前選中的選項
			}
			else {
				cout << "   " << options[i] << " 點" << endl;
			}
		}

		char c = _getch(); // Windows上使用_getch，其他情況下使用getch

		if (c == 'w' || c == 'W') {
			selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
		}
		else if (c == 's' || c == 'S') {
			selectedIndex = (selectedIndex + 1) % options.size();
		}
		else if (c == '\r') { // Enter 鍵
			int selectedFocus = options[selectedIndex];
			setFocus(getFocus() - selectedFocus);
			return selectedFocus;
		}
	}
}


int Role::Flee() {
	return 1;
}