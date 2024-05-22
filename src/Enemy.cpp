#include "Enemy.h"
#include "Dice.h"
#include <conio.h>


void Enemy::selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	int index=rand()%1;
	if (index == 0) {
		normalAttack(role, enemy);
	}
	else if (index == 1) {
		skillAttack(role, enemy);
	}
}
void Enemy::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {
	if (weapon->getType() == 'p') {
		int index = rand() % role.size();
		int n = useFocus(1);
		int absorption = role[index]->getPDefense() / (role[index]->getPDefense() + 50);
		int Attack = getPAttack() * dice(n, 1, getHitRate());
		role[index]->setHp(role[index]->getHp() - Attack * (1 - absorption));
	}

}