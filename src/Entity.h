#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<vector>
#include"Weapon.h"

class Entity {
private:
	int vitality;  // �ͩR��
	int maxFocus;     // �M�`�O
	int speed;     // �t��
	int hitRate;   // �R���v
	int pAttack;   // ���z�����O
	int mAttack;   // �]�k�����O
	int pDefense;  // ���z���m�O
	int mDefense;  // �]�k���m�O
	int focus;	   // ��e�M�`�O
	int Hp;
	Weapon* weapon;
public:
	// Constructor
	int actions;
	std::vector<std::string> buff;
	std::vector<int> buffTime;
	Entity() {
		setVitality(rand() % 15 + 30);  // random value between [30, 45)
		setMaxFocus(3);					// initialize to 3, fixed
		setFocus(3);					// initialize to 3, fixed
		setSpeed(rand() % 25 + 30);		// random value between [30, 55)
		setHitRate(rand() % 20 + 40);	// random value between [40, 60)
		setPAttack(rand() % 11 + 5);	// random value between [5, 15]
		setMAttack(rand() % 11 + 5);	// random value between [5, 15]
		setPDefense(rand() % 21);		// random value between [0, 20]
		setMDefense(rand() % 21);		// random value between [0, 20]
		setHp(getVitality());
		setFocus(getMaxFocus());
		weapon = new Weapon();
	}

	// Getter methods
	int getVitality();
	int getMaxFocus();
	int getSpeed();
	int getHitRate();
	int getPAttack();
	int getMAttack();
	int getPDefense();
	int getMDefense();
	int getFocus();
	int getHp();
	std::string getWeaponName();

	// Setter methods
	void setVitality(int newVitality);
	void setMaxFocus(int newFocus);
	void setSpeed(int newSpeed);
	void setHitRate(int newHitRate);
	void setPAttack(int newPAttack);
	void setMAttack(int newMAttack);
	void setPDefense(int newPDefense);
	void setMDefense(int newMDefense);
	void setHp(int);
	void setFocus(int);

	void normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
	void skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
	bool searchBuff(std::string Buff);
	void giveBuff(std::string Buff, int buffTime);
};
#include"Role.h"
#include"Enemy.h"
#endif // _ENTITY_H_
