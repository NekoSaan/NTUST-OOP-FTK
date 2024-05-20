#pragma once
class Weapon {
public:
	int vitality = 0;  // 生命值
	int speed = 0;     // 速度
	int pAttack = 0;   // 物理攻擊力
	int mAttack = 0;   // 魔法攻擊力
	int pDefense = 0;  // 物理防禦力
	int mDefense = 0;  // 魔法防禦力
	std::string type = "p";	//魔法還是物理
	std::string weaponName = "basic";
	std::string activeSkill = "Null";
	Weapon() {
		vitality = 0;
		speed = 0;
		pAttack = 0;
		mAttack = 0;
		pDefense = 0;
		mDefense = 0;
		type = "p";
	}
	int getVitality(void) { return vitality; }
	int getSpeed(void) { return speed; }
	int getPAttack(void) { return pAttack; }
	int getMAttack(void) { return mAttack; }
	int getPDefense(void) { return pDefense; }
	int getMDefense(void) { return mDefense; }
	std::string getType(void) { return type; }
	std::string getActiveSkill(void) { return activeSkill; }
};
