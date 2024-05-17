#include "Entity.h"
#include <algorithm>
void Entity::setVitality(int newVitality) { vitality = newVitality; }
void Entity::setMaxFocus(int newFocus) { maxFocus = newFocus; }
void Entity::setSpeed(int newSpeed) { speed = newSpeed; }
void Entity::setHitRate(int newHitRate) { hitRate = newHitRate; }
void Entity::setPAttack(int newPAttack) { pAttack = newPAttack; }
void Entity::setMAttack(int newMAttack) { mAttack = newMAttack; }
void Entity::setPDefense(int newPDefense) { pDefense = newPDefense; }
void Entity::setMDefense(int newMDefense) { mDefense = newMDefense; }
void Entity::setHp(int newVitality) { hp = newVitality; }
void Entity::setFocus(int newFocus) { focus = newFocus; }
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
void Entity::normalAttack(Entity* entity) {
}
void Entity::skillAttack(Entity* entity) {

}
