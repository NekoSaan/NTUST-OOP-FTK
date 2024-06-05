#ifndef _ARMOR_H_
#define _ARMOR_H_

#include "Items.h"

// Armor Class, inherti Item Class
class Armor : public Item{
private:
	int vitality;						// Hp
	int speed;							// Speed
	int pDefense;						// Physical defense
	int mDefense;						// Magical defense
	char type;							// Type of equipment
	std::string passiveSkill = "NULL";	// Passive skill

public:
	// Default Constructor
	Armor(std::string, ITEMID);

	// Getter
	int getVitality(void); 
	int getSpeed(void);
	int getPDefense(void);
	int getMDefense(void);
	char getType(void);
	std::string getPassiveSkill(void);

	// equip the armor
	void use(Role*) override;
};

#endif // _ARMOR_H_