#pragma once
#include"Entity.h"
#include"Role.h"
#include"Enemy.h"
#include<vector>
using namespace std;

void combat(vector<Role*> role, vector<Enemy*> enemy) {
	vector<Entity*> entity;

	for (Role* x : role) {
		if (x->searchBuff("Dizziness"))
			entity.push_back(x);
	}

	for (Enemy* x : enemy) {
		if (x->searchBuff("Dizziness"))
			entity.push_back(x);
	}

	for (int i = 0; i < entity.size(); i++) {
		for (int j = i; j < entity.size() - 1; j++) {
			if (entity[i]->getSpeed() > entity[i + 1]->getSpeed()) {
				Entity* temp = entity[i];
				entity[i] = entity[i + 1];
				entity[i + 1] = temp;
			}
		}
	}
}

void attack(Role* attacker, vector<Role*> role, vector<Enemy*> enemy) {
	int index = 0;
	cout << "Which one are you going to attack?";
	cin >> index;
	if (index > enemy.size()) {
		cout << "not vaild";
	}
	else {
		int  skillIndex;
		cout << "Which attack to use ?";
		cin >> skillIndex;
		if (index == 0)
			attacker->normalAttack(enemy[index]);
		else
			attacker->skillAttack(enemy[index]);
	};

}
void attack(Enemy* attacker, vector<Role*> role, vector<Enemy*> enemy) {
	attacker->normalAttack(role[rand() % 1]);
}