#include "Enemy.h"
#include "Dice.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "GameManager.h"
#include "Rect.h"
#include "Combat.h"
#include <conio.h>
#include <cmath>

Enemy::Enemy() : Entity() {
	this->tag = TAG_ENEMY;
	this->icon = 'E';
	this->chosenIndex = 0;

	int randWeapon = rand() % 200 + 1;

	if (randWeapon < 100) {
		randWeapon = rand() % 5 + ITEMID::WoodenSword;
		weapon = new Weapon("Weapon", ITEMID(randWeapon));
	}
	else {
		weapon = new Weapon("Empty", ITEMID::Invalid);
	}
	
	armor = new Armor("Empty", ITEMID::Invalid);
	acc = new Accessory("Empty", ITEMID::Invalid);
};

void Enemy::combatSupport(Role* role) {
	GameManager* gameManager = GameManager::getInstance();
	vector<Entity*> enemies;
	vector<Entity*> roles;
	enemies.push_back(this);
	roles.push_back(role);

	//find role
	for (int i = 0; i < 3; i++) {
		Role* r = gameManager->getRole(i);
		if (r == role) continue;
		if (abs(r->getPos().first - role->getPos().first) + abs(r->getPos().second - role->getPos().second) <= 3) {
			roles.push_back(r);
		}
	}

	//find enemy
	//[y, x]
	int relativePos[24][2] = { {1, 0},  {0, 1}, {-1, 0}, {0, -1},
							   {2, 0}, {1, 1}, {0, 2}, {-1, 1}, {-2, 0}, {-1, -1}, {0, -2}, {1, -1},
							   {3, 0}, {2, 1}, {1, 2}, {0, 3}, {-1, 2}, {-2, 1}, {-3, 0}, {-2, -1}, {-1, -2}, {0, -3}, {1, -2}, {2, -1} };
	for (int i = 0; i < 24; i++) {
		if (!GameManager::isPositionValid(role->getPos().first + relativePos[i][0], role->getPos().second + relativePos[i][1])) continue;
		Object* obj = GameManager::gameBoard[role->getPos().first + relativePos[i][0]][role->getPos().second + relativePos[i][1]].getObject();
		if (obj == NULL) continue;
		if (obj->getTag() == Object::TAG_ENEMY) {
			enemies.push_back((Enemy*)obj);
			if (enemies.size() >= 3) break;
		}
	}

	combat(roles, enemies);
}

int Enemy::selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy) 
{
	int index=rand()%1;
	if (index == 0) {
		normalAttack(role, enemy);
	}
	else if (index == 1) {
		skillAttack(role, enemy);
	}
	return 0;
}

void Enemy::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy)
{
	if (weapon->getType() == 'p') {
		int index = rand() % role.size();
		int absorption = role[index]->getPDefense() / (role[index]->getPDefense() + 50);
		int Attack = getPAttack() * dice(0, 1, getHitRate());
		role[index]->setHp(role[index]->getHp() - Attack * (1 - absorption));
	}

}

void Enemy::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy)
{
}

void Enemy::active(Role* role) {
	switch (chosenIndex) {
	case 0:
		combatSupport(role);
		break;
	case 1:
		exitActive();
		break;
	}
}

void Enemy::chooseActiveUP() {
	chosenIndex--;
	if (chosenIndex < 0) {
		chosenIndex = 1;
	}
}

void Enemy::chooseActiveDown() {
	chosenIndex++;
	if (chosenIndex > 1) {
		chosenIndex = 0;
	}
}

vector<string> Enemy::getAllChoose() {
	vector<string> choose;
	choose.push_back("Fight!");
	choose.push_back("Retreat");
	return choose;
}

int Enemy::getChosenIndex() {
	return chosenIndex;
}

vector<string> Enemy::getDescription() {
	vector<string> description;
	description.push_back("This is an enemy, maybe a goblin");
	description.push_back("HP: " + to_string(hp));
	description.push_back("Physical attack: " + to_string(pAttack));
	description.push_back("Magical attack: " + to_string(mAttack));
	return description;
}