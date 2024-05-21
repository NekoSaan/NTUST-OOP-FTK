#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Weapon;
class Armor;
class Accessory;

class Entity {
private:
	int vitality;  // �ͩR��
	int maxFocus;  // �M�`�O
	int speed;     // �t��
	int hitRate;   // �R���v
	int pAttack;   // ���z�����O
	int mAttack;   // �]�k�����O
	int pDefense;  // ���z���m�O
	int mDefense;  // �]�k���m�O
	int focus;	   // ��e�M�`�O
	int Hp;

public:
	Weapon* weapon;
	int actions;
	std::vector<std::string> buff;
	std::vector<int> buffTime;

	// Constructor
	Entity(void);

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

	int useFocus(int MaxFocus);

	bool searchBuff(std::string);
	void giveBuff(std::string, int);
	void minusBuff();
	void removeBuff(std::string Buff);

	void selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy);
	void normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
	void skillAttack(std::vector<Entity*> role, std::vector<Entity* > enemy);

	void Flee(std::vector<Entity* > role, std::vector<Entity* > enemy);
};

#endif // _ENTITY_H_
