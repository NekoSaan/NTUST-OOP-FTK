#include "Entity.h"
#include "Dice.h"
#include "Weapon.h"
#include <conio.h>
#include <algorithm>

Entity::Entity(void) {
	setVitality(rand() % 15 + 30);  // random value between [30, 45)
	setMaxFocus(3);					// initialize to 3, fixed
	setFocus(3);					// initialize to 3, fixed
	setSpeed(rand() % 25 + 30);		// random value between [30, 55)
	setHitRate(rand() % 20 + 40);	// random value between [40, 60)
	setPAttack(rand() % 11 + 5);	// random value between [5, 15]
	setMAttack(rand() % 11 + 5);	// random value between [5, 15]
	setPDefense(rand() % 21);		// random value between [0, 20]
	setMDefense(rand() % 21);		// random value between [0, 20]
	setHp(getVitality());
	setFocus(getMaxFocus());

	weapon = new Weapon("Bug", ITEMID::Invalid);
}

void Entity::setVitality(int newVitality) { vitality = newVitality; }
void Entity::setMaxFocus(int newFocus) { maxFocus = newFocus; }
void Entity::setSpeed(int newSpeed) { speed = newSpeed; }
void Entity::setHitRate(int newHitRate) { hitRate = newHitRate; }
void Entity::setPAttack(int newPAttack) { pAttack = newPAttack; }
void Entity::setMAttack(int newMAttack) { mAttack = newMAttack; }
void Entity::setPDefense(int newPDefense) { pDefense = newPDefense; }
void Entity::setMDefense(int newMDefense) { mDefense = newMDefense; }
void Entity::setFocus(int newFocus) { focus = newFocus; }
void Entity::setHp(int newHp) { Hp = newHp; }

bool Entity::searchBuff(std::string Buff) {
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	return it != buff.end();
}
void Entity::giveBuff(std::string Buff, int BuffTime) {
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	if (it != buff.end()) {
		buff.push_back(Buff);
		buffTime.push_back(BuffTime);
	}
	else {
		buffTime[it - buff.begin()] = BuffTime;
	}
}
void  Entity::minusBuff() {
	for (int i = 0; i < buffTime.size(); i++) {
		buffTime[i]--;

		if (buffTime[i] < 0) {
			removeBuff(buff[i]);
		}
	}
}
void  Entity::removeBuff(std::string Buff) {
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);
	int index = std::distance(buff.begin(), it);
	buff.erase(it);
	buffTime.erase(buffTime.begin() + index);
}

int Entity::getVitality() {
	int Vitality = vitality; // + weapon->getVitality();

	return std::min(100, Vitality);
}
int Entity::getMaxFocus() {
	return maxFocus;
}

int Entity::getSpeed() {
	int Speed = speed + weapon->getSpeed();

	if (searchBuff("SpeedUp")) {
		Speed *= 1.5;
	}

	return std::min(100, Speed);
}
int Entity::getHitRate() {
	int HitRate = hitRate;

	if (searchBuff("Angle")) {
		HitRate -= 30;
	}

	return std::min(100, HitRate);
}
int Entity::getPAttack() {
	int PAttack = pAttack + weapon->getPAttack();

	return std::min(100, PAttack);
}
int Entity::getMAttack() {
	int MAttack = mAttack + weapon->getMAttack();

	return std::min(100, MAttack);
}
int Entity::getPDefense() {
	int PDefense = pDefense + weapon->getPDefense();

	return std::min(100, PDefense);
}
int Entity::getMDefense() {
	int MDefense = mDefense + weapon->getMDefense();

	return std::min(100, mDefense);
}
int Entity::getFocus() {
	return focus;
}
int Entity::getHp() {
	return Hp;
}

std::string Entity::getWeaponName() {
	return weapon->weaponName;
}

void Entity::selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	char c = _getch();
	if (c == '0') {
		normalAttack(role, enemy);
	}
	else if (c == '1') {
		skillAttack(role, enemy);
	}
	else if (c == '3') {
		Flee(role, enemy);
	}
}

void Entity::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	if (weapon->getType() == "p") {
		char c = _getch();
		int n = useFocus(1);
		int absorption = enemy[(int)c]->getPDefense() / (getPDefense() + 50);
		int Attack = getPAttack() * dice(n, 1, getHitRate());
		enemy[0]->setHp(enemy[(int)c]->getHp() - Attack * (1 - absorption));
	}

}
void Entity::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	if (weapon->getActiveSkill() == "Provoke") {
		int HitRate = getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed();
		char c = _getch();
		int n = useFocus(1);

		if (dice(n, 1, HitRate) == 1) {
			enemy[(int)c]->giveBuff("Angry", 3);
		}
	}
}

int Entity::useFocus(int MaxFocus) {
	while (1) {
		char c = _getch();
		int n = (int)c;

		if (n > getFocus() || n > MaxFocus) {
			std::cout << "fail";
			continue;
		}
		else {
			setFocus(getFocus() - n);
			return n;
		}
	}

}

void Entity::Flee(std::vector<Entity* > role, std::vector<Entity* > enemy) {

}
