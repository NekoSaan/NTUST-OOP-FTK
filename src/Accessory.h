#ifndef _ACCESSORY_H_
#define _ACCESSORY_H_
#include "Items.h"

// Accessory Class, inherti Item Class
class Accessory : public Item {
private:
	int mDefense;	// get magical defense
	int speed;		// get speed up
	int maxFocus;	// get inc focus
	std::string passiveSkill = "NULL";

public:
	// Assign Constructor
	Accessory(std::string, ITEMID);

	// Get magical defense
	int getMDefense(void) const;

	// Get speed
	int getSpeed(void) const;

	// Get max focus
	int getMaxFocus(void) const;

	// Get passive skill
	std::string getPassiveSkill(void) const;
	  
	// Equipment equip by role
	void use(Role*) override;
};

#endif // _ACCESSORY_H_
