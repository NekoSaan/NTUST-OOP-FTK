#pragma once
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
	Entity* actor = entity[0];
	for (int i = 0; i < entity.size(); i++) {
		if ((entity[i]->actions + 1) / entity[i]->getSpeed() < (actor->actions + 1) / actor->getSpeed()) {
			actor = entity[i];
		}
		else if ((entity[i]->actions + 1) / entity[i]->getSpeed() == (actor->actions + 1) / actor->getSpeed()) {
			if (entity[i]->getSpeed() > actor->getSpeed()) {
				actor = entity[i];
			}
			else if (entity[i]->getSpeed() == actor->getSpeed()) {
				if (entity[i]->getPAttack() + entity[i]->getMAttack() > actor->getPAttack() + actor->getMAttack()) {
					actor = entity[i];
				}
				else if (entity[i]->getPAttack() + entity[i]->getMAttack() == actor->getPAttack() + actor->getMAttack()) {
					if (entity[i]->getPDefense() + entity[i]->getMDefense() > actor->getPDefense() + actor->getMDefense()) {
						actor = entity[i];
					}
					else if (entity[i]->getVitality() > actor->getVitality()) {
						actor = entity[i];
					}
				}
			}
		}
	}
	Move(actor, role, enemy);
	// �����w���Ѫ�����
	for (auto it = role.begin(); it != role.end(); ) {
		if ((*it)->getHp() <= 0) {
			(*it)->actions = 0;
			it = role.erase(it);
		}
		else {
			++it;
		}
	}
	// �����w���Ѫ��ĤH
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