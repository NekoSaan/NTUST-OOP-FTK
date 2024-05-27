#ifndef _COMBAT_H_
#define _COMBAT_H_
#include "Entity.h"
#include "GameManager.h"
#include"Weapon.h"

using namespace std;

int Action(Entity* actor, vector<Entity*>role, vector<Entity*>enemy) {
	actor->actions++;
	if (actor->searchBuff("Ditness") == 0) {
		if (actor->selectAction(role, enemy) == 1) {
			return 1;
		}
	}
	if (actor->searchBuff("Poisoned") == 1) {
		actor->setHp(max(actor->getHp() / 10, 1));
	}
	actor->minusBuff();
	actor->weapon->setCD(max(actor->weapon->getCD()-1, 0));
	return 0;
}
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
		if ((entity[i]->actions + 1) *100/ entity[i]->getSpeed() < (actor->actions + 1) * 100 / actor->getSpeed()) {
			actor = entity[i];
		}
		else if ((entity[i]->actions + 1) * 100 / entity[i]->getSpeed() == (actor->actions + 1) * 100 / actor->getSpeed()) {
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
	
	if (Action(actor, role, enemy) == 1) {
		auto it = std::find(role.begin(), role.end(), actor);
		if (it != role.end()) {
			role.erase(it);
		}
	}
	
	// 移除已擊敗的角色
	for (auto it = role.begin(); it != role.end(); ) {
		if ((*it)->getHp() <= 0) {
			(*it)->actions = 0;
			(*it)->weapon->setCD(0);
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
			(*it)->weapon->setCD(0);
			it = enemy.erase(it);
		}
		else {
			++it;
		}
	}
	if (!role.empty() && !enemy.empty()) {
		combat(role, enemy);
	}
	else {
		for (Entity* x : entity) {
			x->actions = 0;
			x->weapon->setCD(0);

		}
	}
}

#endif // _COMBAT_H_
