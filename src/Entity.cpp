#include "Entity.h"
#include <algorithm>
#include"dice.h"
#include<conio.h>

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
		return 1;
	}
	else {
		return 0;
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
void  Entity::minusBuff() {
	for (int i = 0; i < buffTime.size(); i++) {
		buffTime[i]--;
		if (buffTime[i] < 0)
			removeBuff(buff[i]);
	}
}
void  Entity::removeBuff(std::string Buff) {
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);
	int index = std::distance(buff.begin(), it);
	buff.erase(it);
	buffTime.erase(buffTime.begin() + index);


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


void Entity::selectAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	char c = _getch();
	if (c == '0')
		normalAttack(role, enemy);
	else if (c == '1')
		skillAttack(role, enemy);
}

void Entity::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	if (weapon->getType() == "p") {
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