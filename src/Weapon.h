#pragma once
class Weapon {
public:
	int vitality = 0;  // �ͩR��
	int speed = 0;     // �t��
	int pAttack = 0;   // ���z�����O
	int mAttack = 0;   // �]�k�����O
	int pDefense = 0;  // ���z���m�O
	int mDefense = 0;  // �]�k���m�O
	std::string type = "p";	//�]�k�٬O���z
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
