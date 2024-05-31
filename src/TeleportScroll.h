#ifndef _TELEPORTSCROLL_H_
#define _TELEPORTSCROLL_H_
#include "Items.h"

class TeleportScrool : public Item
{
public:
	// Constructor for Weapon class
	TeleportScrool(std::string);
	
	void use(Role*) override;
};

#endif _TELEPORTSCROLL_H_
