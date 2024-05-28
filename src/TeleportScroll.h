#ifndef _TELEPORTSCROLL_H_
#define _TELEPORTSCROLL_H_
#include "Items.h"

class TeleportScrool : public Item
{
private:
	int originalY, originalX;

public:
	// Constructor for Weapon class
	TeleportScrool(Role* role, std::string);
	
	void use(Role*) override;
};

#endif _TELEPORTSCROLL_H_
