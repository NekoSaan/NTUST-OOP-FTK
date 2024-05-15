#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
class Entity {
private:
	int vitality;  // 生命值
	int focus;     // 專注力
	int speed;     // 速度
	int hitRate;   // 命中率
	int pAttack;   // 物理攻擊力
	int mAttack;   // 魔法攻擊力
	int pDefense;  // 物理防禦力
	int mDefense;  // 魔法防禦力

public:
	// Constructor
	Entity() {
		srand(time(NULL));  // 初始化隨機種子
		setVitality(rand() % 15 + 30);  // [30, 45) 的隨機數
		setFocus(3);  // 專注力固定為 3
		setSpeed(rand() % 25 + 30);  // [30, 55) 的隨機數
		setHitRate(rand() % 20 + 40);  // [40, 60) 的隨機數
		setPAttack(rand() % 11 + 5);  // [5, 15] 的隨機數
		setMAttack(rand() % 11 + 5);  // [5, 15] 的隨機數
		setPDefense(rand() % 21);  // [0, 20] 的隨機數
		setMDefense(rand() % 21);  // [0, 20] 的隨機數
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