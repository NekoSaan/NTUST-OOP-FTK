#pragma once
#include"Entity.h"
class Role : public Entity {
	Role() : Entity() {
		srand(time(0));  // ��l���H���ؤl
		setVitality(rand() % 15 + 30);  // [30, 45) ���H����
		setFocus(3);  // �M�`�O�T�w�� 3
		setSpeed(rand() % 25 + 30);  // [30, 55) ���H����
		setHitRate(rand() % 20 + 40);  // [40, 60) ���H����
		setPAttack(rand() % 11 + 5);  // [5, 15] ���H����
		setMAttack(rand() % 11 + 5);  // [5, 15] ���H����
		setPDefense(rand() % 21);  // [0, 20] ���H����
		setMDefense(rand() % 21);  // [0, 20] ���H����
	}

};
