#include "Items.h"
#include "Role.h"
#include "GameManager.h"
#include "Rect.h"
#include "TeleportScroll.h"
#include "Tent.h"

// Intent: Retrieve the list of item names
// Pre: None
// Post: Returns a vector of strings containing the names of all items available in the game
std::vector<std::string> getItemList(void) {
	// Define the list of item names
	std::vector<std::string> ItemList = {
		// Consumables
		"Godsbeard",
		"GoldenRoot",
		"TeleportScroll",
		"Tent",

		// Equipments, non-stackable
		// Weapons
		"WoodenSword",
		"Hammer",
		"GiantHammer",
		"MagicWand",
		"RitualSword",
		// Armor
		"WoodenShield",
		"PlateArmor",
		"LeatherArmor",
		"Robe",
		"LaurelWreath",
		// Accessory
		"HolyGrail",
		"Shoes",
		"Bracelet",
		" "
	};

	// Return the list of item names
	return ItemList;
}

// Intent: Constructor for the Item class initializing member variables to default values
// Pre: None
// Post: Initializes an Item instance with default values (tag as "Empty", id as Invalid, amount as 0)
Item::Item(void) : tag("Empty"), id(ITEMID::Invalid), amount(0) {};

// Intent: Construct an Item object with specified tag and id, initializing amount to 1
// Pre: None
// Post: Constructs an Item object with specified tag, id, and amount
Item::Item(std::string tag, ITEMID id) : tag(tag), id(id), amount(1) {
	itemName = getItemList()[(int)id];
};

// Intent: Destruct an Item object
// Pre: None
// Post: Clears the itemName, des, id, and amount of the Item object
Item::~Item(void) {
	itemName = "";
	//des = "";
	id = ITEMID::Invalid;
	amount = NULL;
}

// Intent: Get the id of the Item object
// Pre: None
// Post: Returns the id of the Item object
int Item::getId(void) {
	return (int)id;
}

// Intent: Get the amount of the Item object
// Pre: None
// Post: Returns the amount of the Item object
int Item::getAmount(void) {
	return amount;
}

// Intent: Increment the amount of the Item object by 1
// Pre: None
// Post: Increases the amount of the Item object by 1
void Item::incAmount(void) {
	amount++;
}

// Intent: Decrement the amount of the Item object by 1
// Pre: None
// Post: Decreases the amount of the Item object by 1
void Item::decAmount(void) {
	amount--;
}

// Intent: Get the tag of the Item object
// Pre: None
// Post: Returns the tag of the Item object
std::string Item::getTag(void) {
	return tag;
}

// Intent: Get the name of the Item object
// Pre: None
// Post: Returns the name of the Item object
std::string Item::getName(void) {
	return itemName;
}

// Intent: Perform action based on the item's id
// Pre: role must be a valid Role object
// Post: Performs an action based on the item's id; if the id is not recognized, no action is taken
// \param role: use item character
void Item::use(Role* role) {
	Rect* rect = &GameManager::gameBoard[role->getPos().first][role->getPos().second];
	TeleportScrool temp("Consuable");

	switch (id) {
	case ITEMID::Godsbeard:
		role->gainHealth(25);
		break;
	case ITEMID::GoldenRoot:
		role->gainFocus(3);
		break;
	case ITEMID::TeleportScroll:
		temp.use(role);
		break;
	case ITEMID::Tent:
		rect->setObject(new Tent(rect));
		break;
	default:
		// nothing happened, invalid id
		break;
	}
}