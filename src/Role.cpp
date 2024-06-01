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
	lastPos.first = this->y;
	lastPos.second = this->x;
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

void Role::moveTolastPos() {
	setPos(lastPos.first, lastPos.second);
}

void Role::gainHealth(int healHp) {
	hp = min(hp + healHp, vitality);
}

void Role::gainFocus(int restoreN) {
	focus = min(focus + restoreN, maxFocus);
}

void Role::setMovementPoint() {
	int maxMovementPoint = speed / 10;
	if (getPassiveSkill("Run")) {
		movementPoint = dice(1, maxMovementPoint, speed);
	}
	else {
		movementPoint = dice(0, maxMovementPoint, speed);
	}
	
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
		vector<string> combatList, combatInfo;
		combatList.push_back("�п�ܤ@�ӥؼСG");

		for (size_t i = 0; i < enemy.size(); ++i) {
			if (i == selectedIndex) {
				combatList.push_back(">"+enemy[i]->getName());
			}
			else {
				combatList.push_back(" " + enemy[i]->getName());
			}
		}

		gameManager->battleScreen(role, enemy, combatList, { "" });

		char c = getch(); 

		if (c == 'w' || c == 'W') {
			selectedIndex = (selectedIndex - 1 + enemy.size()) % enemy.size();
		}
		else if (c == 's' || c == 'S') {
			selectedIndex = (selectedIndex + 1) % enemy.size();
		}
		else if (c == '\r') { // Enter ��
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
	int numOptions = 2;  // Number of options in the menu
	vector<string> combatAction;
	combatAction.push_back("Normal Attack");
	combatAction.push_back("Flee");
	if (weapon->getActiveSkill() != "NULL") {
		numOptions++;
		combatAction.push_back(weapon->getActiveSkill());
	}
	/*if (getAmoutOfGold() >0) {
		numOptions++;
		combatAction.push_back(Goldenroot);
	}*/
	while (true) {
		vector<string> combatList, combatInfo;
		combatList.push_back("Select your action");		
		// Display menu with highlighted selected option
		for (int i = 0; i < numOptions; ++i) {
			string action = "";

			if (i == selectedOption) {
				action += "-> ";
			}
			else {
				action += "   ";
			}
			action += combatAction[i];
			combatList.push_back(action);
		}

		gameManager->battleScreen(role, enemy, combatList, { "attacker: "+getName(),sort });

		char input = getch();

		// Handle arrow keys for navigation
		if (input == 'w' && selectedOption > 0) {
			selectedOption--;
		}
		else if (input == 's' && selectedOption < numOptions - 1) {
			selectedOption++;
		}
		else if (input == '\r') {  // '\r' is Enter key
			if (combatAction[selectedOption] == "Normal Attack") {
				normalAttack(role, enemy);
				return 0;
			}
			else if(combatAction[selectedOption] == "Flee"){
				if (Flee(role, enemy) == 1) {
					return 1;
				}
				return 0;
			}
			else if (combatAction[selectedOption] == weapon->getActiveSkill()) {
				skillAttack(role, enemy);
				return 0;
			}
			else if (combatAction[selectedOption] == "Goldenroot") {
				//use Goldenroot
			}
		}	
	}	
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
		enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() - attack * (1 - absorption)*((enemy[targetIndex]->getPassiveSkill("Fortify") == 1)?0.9:1));
		
		if (getPassiveSkill("Hammer-Splash") == 1 && attack==getPAttack()) {
			enemy[targetIndex]->giveBuff("Dizziness", 3);
			for (int i = 0; i < enemy.size(); i++) {
				if (i != targetIndex) {
					enemy[i]->setHp(enemy[i]->getHp() - attack * 1-(enemy[i]->getPDefense() / (enemy[i]->getPDefense() + 50)));
				}
			}
		}
	}
	else {
		int n = useFocus(1,role, enemy);
		int absorption = enemy[targetIndex]->getMDefense() / (getMDefense() + 50);
		int attack = getMAttack() * dice(n, 1, getHitRate());
		enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() - attack * (1 - absorption)*((enemy[targetIndex]->getPassiveSkill("Fortify") == 1) ? 0.9 : 1));
		if (getPassiveSkill("Hammer-Splash") == 1 && attack == getMAttack()) {
			enemy[targetIndex]->giveBuff("Dizziness", 3);
			for (int i = 0; i < enemy.size(); i++) {
				if (i != targetIndex) {
					enemy[i]->setHp(enemy[i]->getHp() - attack * 1 - (enemy[i]->getMDefense() / (enemy[i]->getMDefense() + 50)));
				}
			}
		}
	}
	if (getPassiveSkill("Destroy") == 1) {
		int index = rand() % 3;
		switch (index) {
			case(0):
				enemy[targetIndex]->weapon;
				break;
				}
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
		
		int targetIndex = selectTarget(enemy, role);
		int n = useFocus(2,role, enemy);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[targetIndex]->setHp(role[targetIndex]->getHp() + getMAttack() * 3 / 2);
		}
		weapon->setCD(2);
	}
	else if (weapon->getActiveSkill() == "SpeedUp")
	{
		int targetIndex = selectTarget(enemy, role);
		int n = useFocus(2, role, enemy);

		if (dice(n, 2, getHitRate()) == 2)
		{
			role[(targetIndex+1)%role.size()]->giveBuff("SpeedUp", 3);
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
		vector<string> combatList, combatInfo;
		combatList.push_back("�п�ܭn�ϥΪ��M�`�ȡG");

		for (size_t i = 0; i < options.size(); ++i) {
			if (i == selectedIndex) {
				// current target
				combatList.push_back(" > " + to_string(options[i]) + " �I");
			}
			else {
				combatList.push_back("   " + to_string(options[i]) + " �I");
			}
		}

		gameManager->battleScreen(role, enemy, combatList, { "" });

		char c = _getch(); 

		if (c == 'w' || c == 'W') {
			selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
		}
		else if (c == 's' || c == 'S') {
			selectedIndex = (selectedIndex + 1) % options.size();
		}
		else if (c == '\r') { // Enter ��
			int selectedFocus = options[selectedIndex];
			setFocus(getFocus() - selectedFocus);

			return selectedFocus;
		}
	}
}


int Role::Flee(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	int n = useFocus(1, role, enemy);
	int HitRate = min(getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed(),98);
	if (dice(n, 1, HitRate) == 1)
	{
		return 1;
	}
	return 0;
}

