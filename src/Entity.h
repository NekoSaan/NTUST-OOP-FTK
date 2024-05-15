#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
class Entity {
private:
	int vitality;  // �ͩR��
	int focus;     // �M�`�O
	int speed;     // �t��
	int hitRate;   // �R���v
	int pAttack;   // ���z�����O
	int mAttack;   // �]�k�����O
	int pDefense;  // ���z���m�O
	int mDefense;  // �]�k���m�O

public:
	// Constructor
	Entity() {
		srand(time(NULL));  // ��l���H���ؤl
		setVitality(rand() % 15 + 30);  // [30, 45) ���H����
		setFocus(3);  // �M�`�O�T�w�� 3
		setSpeed(rand() % 25 + 30);  // [30, 55) ���H����
		setHitRate(rand() % 20 + 40);  // [40, 60) ���H����
		setPAttack(rand() % 11 + 5);  // [5, 15] ���H����
		setMAttack(rand() % 11 + 5);  // [5, 15] ���H����
		setPDefense(rand() % 21);  // [0, 20] ���H����
		setMDefense(rand() % 21);  // [0, 20] ���H����
	}

	// Getter methods
	int getVitality() { return vitality; }
	int getFocus() { return focus; }
	int getSpeed() { return speed; }
	int getHitRate() { return hitRate; }
	int getPAttack() { return pAttack; }
	int getMAttack() { return mAttack; }
	int getPDefense() { return pDefense; }
	int getMDefense() { return mDefense; }

	// Setter methods
	void setVitality(int newVitality);
	void setFocus(int newFocus);
	void setSpeed(int newSpeed);
	void setHitRate(int newHitRate);
	void setPAttack(int newPAttack);
	void setMAttack(int newMAttack);
	void setPDefense(int newPDefense);
	void setMDefense(int newMDefense);
};