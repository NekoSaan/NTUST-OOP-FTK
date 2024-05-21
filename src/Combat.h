#ifndef _COMBAT_H_
#define _COMBAT_H_
#include"Entity.h"
#include<vector>
using namespace std;

void combat(vector<Entity*> role, vector<Entity*> enemy) {
	vector<Entity*> entity;
	for (Entity* x : role) {
		entity.push_back(x);
	}
	for (Entity* x : enemy) {
		entity.push_back(x);
	}
	
	for (int i = 0; i < entity.size(); i++) {
		for (int j = i; j < entity.size()-1; j++) {
			if ((entity[j]->actions + 1) / entity[j]->getSpeed() < (entity[j+1]->actions + 1) / entity[j + 1]->getSpeed()) {
				std::swap(entity[j], entity[j + 1]);
			}
			else if ((entity[j]->actions + 1) / entity[j]->getSpeed() == (entity[j+1]->actions + 1) / entity[j+1]->getSpeed()) {
				if (entity[j]->getSpeed() > entity[j+1]->getSpeed()) {
					std::swap(entity[j], entity[j + 1]);
				}
				else if (entity[j]->getSpeed() == entity[j+1]->getSpeed()) {
					if (entity[j]->getPAttack() + entity[j]->getMAttack() > entity[j+1]->getPAttack() + entity[j+1]->getMAttack()) {
						std::swap(entity[j], entity[j + 1]);
					}
					else if (entity[j]->getPAttack() + entity[j]->getMAttack() == entity[j+1]->getPAttack() + entity[j+1]->getMAttack()) {
						if (entity[j]->getPDefense() + entity[j]->getMDefense() > entity[j+1]->getPDefense() + entity[j+1]->getMDefense()) {
							std::swap(entity[j], entity[j + 1]);
						}
						else if (entity[j]->getVitality() > entity[j+1]->getVitality()) {
							std::swap(entity[j], entity[j + 1]);
						}
					}
				}
			}
		}
	}
	Move(entity.back(), role, enemy);
	// 移除已擊敗的角色
	for (auto it = role.begin(); it != role.end(); ) {
		if ((*it)->getHp() <= 0) {
			(*it)->actions = 0;
			it = role.erase(it);
		}
		else {
			++it;
		}
	}
	// 移除已擊敗的敵人
	for (auto it = enemy.begin(); it != enemy.end(); ) {
		if ((*it)->getHp() <= 0) {
			(*it)->actions = 0;
			it = enemy.erase(it);
		}
		else {
			++it;
		}
	}
	if (role.empty() || role.empty()) {
		combat(role, enemy);
	}
	else {
		for (Entity* x : entity) {
			x->actions = 0;
		}
	}
}

void Move(Entity* attacker, vector<Entity*> role, vector<Entity*> enemy) {
	attacker->actions++;
	if(attacker->searchBuff("Ditness")==0)
		attacker->selectAction(role, enemy);
	attacker->minusBuff();
}

#endif // _COMBAT_H_
