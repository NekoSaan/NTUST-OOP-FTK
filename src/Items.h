#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <string>
#include <vector>

enum ITEMID {
	Godsbeard,
	GoldenRoot,
	TeleportScroll,
	Tent,
	Invalid,
};

std::vector<std::string> ItemList = {
	"Godsbeard",
	"GoldenRoot",
	"TeleportScroll",
	"Tent",
	"DummyItemForTest"
};

class Item {
protected:
	std::string tag;
	std::string itemName;
	std::string des;
	ITEMID id;

public:
	int amount;

	Item(std::string, ITEMID);

	int getId(void);

	std::string getName(void);

	// void use(Role* role);
};

Item::Item(std::string tag, ITEMID id) : tag(tag), id(id), itemName(ItemList[id]), amount(1) {};

int Item::getId(void) {
	return id;
}

std::string Item::getName(void) {
	return itemName;
}

#endif // _ITEMS_H_