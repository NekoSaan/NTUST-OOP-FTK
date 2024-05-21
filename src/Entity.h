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
	int vitality;  // 生命值
	int maxFocus;  // 專注力
	int speed;     // 速度
	int hitRate;   // 命中率
	int pAttack;   // 物理攻擊力
	int mAttack;   // 魔法攻擊力
	int pDefense;  // 物理防禦力
	int mDefense;  // 魔法防禦力
	int focus;	   // 當前專注力
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
