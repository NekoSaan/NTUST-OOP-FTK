#ifndef _COMBAT_H_
#define _COMBAT_H_
#include "Entity.h"
#include "GameManager.h"
#include"Weapon.h"
#include<algorithm>

using namespace std;

bool compareEntities(Entity* a, Entity* b) {
	// Compare based on priority criteria
	if ((a->actions + 1) * 100 / a->getSpeed() != (b->actions + 1) * 100 / b->getSpeed())
		return ((a->actions + 1) * 100 / a->getSpeed()) < ((b->actions + 1) * 100 / b->getSpeed());
	if (a->getSpeed() != b->getSpeed())
		return a->getSpeed() > b->getSpeed();
	if ((a->getPAttack() + a->getMAttack()) != (b->getPAttack() + b->getMAttack()))
		return (a->getPAttack() + a->getMAttack()) > (b->getPAttack() + b->getMAttack());
	if ((a->getPDefense() + a->getMDefense()) != (b->getPDefense() + b->getMDefense()))
		return (a->getPDefense() + a->getMDefense()) > (b->getPDefense() + b->getMDefense());
	return a->getVitality() > b->getVitality();
}
int Action(Entity* actor, vector<Entity*>role, vector<Entity*>enemy) {
	actor->actions++;

	if (actor->searchBuff("Dizziness") == 0) {
		if (actor->selectAction(role, enemy) == 1) {
			return 1;
		}
	}

	if (actor->searchBuff("Poisoned") == 1) {
		actor->setHp(max(actor->getHp() / 10, 1));
	}

	actor->minusBuff();
	actor->weapon->setCD(max(actor->weapon->getCD() - 1, 0));
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

	std::sort(entity.begin(), entity.end(), compareEntities);
	string sort;

	for (int i = 0; i < entity.size(); i++) {
		sort += entity[i]->getName();

		if (i != entity.size() - 1) {
			sort += " <- ";
		}
	}

	// Now entity vector is sorted based on the defined criteria
	// The first element will be the entity with the highest priority
	Entity* actor = entity[0];
	actor->sort = sort;
	//actor->giveBuff("Dizziness", 1);

	if (Action(actor, role, enemy) == 1) {
		auto it = std::find(role.begin(), role.end(), actor);

		if (it != role.end()) {
			(*it)->actions = 0;
			(*it)->buff.clear();
			role.erase(it);
		}
	}
	
	// 移除已擊敗的角色
	for (auto it = role.begin(); it != role.end(); ) {
		if ((*it)->getHp() <= 0) {
			(*it)->actions = 0;
			(*it)->weapon->setCD(0);
			(*it)->setHp(0);
			(*it)->buff.clear();
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
		//exit combat
		for (Entity* x : entity) {
			x->actions = 0;
			x->weapon->setCD(0);
			x->buff.clear();
		}

		system("CLS");
	}
}

#endif // _COMBAT_H_
