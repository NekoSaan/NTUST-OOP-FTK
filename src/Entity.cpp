#include "Entity.h"
#include"dice.h"
#include <algorithm>
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

	if (it != buff.end()) {
		return 0;
	}
	else {
		return 1;
	}

	return 0;
}
void  Entity::giveBuff(std::string Buff, int BuffTime) {
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);
	if (it != buff.end()) {
		buff.push_back(Buff);
		buffTime.push_back(BuffTime);
	}
	else {
		buffTime[it - buff.begin()] = BuffTime;
	}
}
void Entity::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	if (weapon->type == "p") {
		int absorption = enemy[0]->getPDefense() / (getPDefense() + 50);
		int n = 0;
		std::cin >> n;
		if (n > getFocus())
			std::cout << "fail";
		else
			setFocus(getFocus() - n);
		int Attack = getPAttack() * dise(n, 1, getHitRate());
		enemy[0]->setHp(enemy[0]->getHp() - Attack * (1 - absorption));
	}

}
void Entity::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {

}
int Entity::getVitality() {
	int Vitality = vitality;// + weapon->getVitality();
	if (Vitality > 100)
		return 100;
	else
		return Vitality;
}
int Entity::getMaxFocus() {
	return maxFocus;
}
int Entity::getSpeed() {
	int Speed = speed + weapon->getSpeed();
	if (searchBuff("SpeedUp"))
		Speed *= 1.5;
	if (Speed > 100)
		return 100;
	else
		return Speed;
}
int Entity::getHitRate() {
	int HitRate = hitRate;
	if (searchBuff("Angle"))
		HitRate -= 30;
	if (HitRate < 0)
		return 0;
	else
		return HitRate;
}
int Entity::getPAttack() {
	int PAttack = pAttack + weapon->getPAttack();
	if (PAttack > 100)
		return 100;
	else
		return PAttack;
}
int Entity::getMAttack() {
	int MAttack = mAttack + weapon->getMAttack();
	if (MAttack > 100)
		return 100;
	else
		return MAttack;
}
int Entity::getPDefense() {
	int PDefense = pDefense + weapon->getPDefense();
	if (PDefense > 100)
		return 100;
	else
		return PDefense;
}
int Entity::getMDefense() {
	int MDefense = mDefense + weapon->getMDefense();
	if (MDefense > 100)
		return 100;
	else
		return MDefense;
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