#ifndef _ACCESSORY_H_
#define _ACCESSORY_H_
#include "Items.h"

class Accessory : public Item {
private:
	int mDefense;						// get magical defense
	int speed;							// get speed up
	int maxFocus;						// get inc focus
	std::string activeSkill = "NULL";	// Active skill associated with the weapon

public:
	Accessory(std::string, ITEMID);

	int getMDefense(void);
	int getSpeed(void);
	int getMaxFocus(void);

	void use(Role*) override;
};

#endif // _ACCESSORY_H_
