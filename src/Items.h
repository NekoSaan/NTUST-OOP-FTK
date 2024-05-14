#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <string>
#include <vector>

class Role;

enum ITEMID {
	// Consumables, stackable
	Godsbeard = 0,
	GoldenRoot,
	TeleportScroll,
	Tent,

	// Equipments, non-stackable
	WoodenSword,
	Hammer,
	MagicWand,
	Shoes,
	PlateArmor,
	Bracelet,
	Invalid,
};

extern std::vector<std::string> ItemList;

class Item {
protected:
	std::string tag;
	std::string itemName;
	std::string des;
	ITEMID id;
	int amount;

public:

	Item(std::string, ITEMID);

	~Item(void);

	int getId(void);

	int getAmount(void);

	void incAmount(void);

	void decAmount(void);

	std::string getTag(void);

	std::string getName(void);

	virtual void use(Role*);
};

#endif // _ITEMS_H_