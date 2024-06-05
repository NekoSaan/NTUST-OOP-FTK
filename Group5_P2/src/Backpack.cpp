#include "Backpack.h"
#include "Items.h"
#include "Weapon.h"
#include "GameManager.h"
#include "Role.h"

BackPack bag; // Initialize

// Intent: Class constructor
// Pre: None
// Post: Constructs a BackPack object with an initial money value of 600 and initializes inventory with default items.
BackPack::BackPack(void) : money(600)
{
	// Initial Supplies or nothing
	for (int i = 0; i < (int)ITEMID::WoodenSword; i++)  {
		
		// Get 10 teleport for demo.
		if (i == (int)ITEMID::TeleportScroll) {

			// The obtain item loop
			for (size_t j = 0; j < 10; j++) {
				obtainItem(new Item("Consumable", ITEMID(i)));
			}
			continue;
		}

		obtainItem(new Item("Consumable", ITEMID(i)));
	}
}

// Intent: Add an item to the inventory
// Pre: item must be a valid pointer to an Item object
// Post: Adds the item to the inventory or increments its amount if it already exists in the inventory
void BackPack::obtainItem(Item* item) 
{
	// Item wasn't a consumable, directly push back it into inventory
	if (item->getId() > (int)ITEMID::Tent) {
		inventory.push_back(item);
		return;
	}

	// Otherwise, try to find it in inventory to stack.
	for (size_t i = 0; i < inventory.size(); i++) {
		if (item->getId() == inventory[i]->getId()) {
			inventory[i]->incAmount();

			delete item;
			item = nullptr;
			return;
		}
	}

	inventory.push_back(item);
}

// Intent: Get the current amount of money
// Pre: None
// Post: Returns the amount of money in the backpack
int BackPack::getMoney(void) {
	return money;
}

// Intent: Get the current index in the inventory
// Pre: None
// Post: Returns the current index in the inventory
int BackPack::getCurIndex() {
	return curIndex;
}

// Intent: Get the current page in the inventory
// Pre: None
// Post: Returns the current page in the inventory
int BackPack::getCurPage() {
	return curPage;
}

// Intent: Get the maximum page in the inventory
// Pre: None
// Post: Returns the maximum page in the inventory
int BackPack::getMaxPage() {
	return maxPage;
}

// Intent: Get the size of the inventory
// Pre: None
// Post: Returns the size of the inventory
int BackPack::getInventorySize() { 
	return (int)inventory.size(); 
}

// Intent: Get the name of the item at the specified index in the inventory
// Pre: i must be a valid index within the inventory range
// Post: Returns the name of the item at the specified index in the inventory
std::string BackPack::getItemName(int i) { 
	return inventory[i]->getName(); 
}

// Intent: Get the amount of the item at the specified index in the inventory
// Pre: i must be a valid index within the inventory range
// Post: Returns the amount of the item at the specified index in the inventory
int BackPack::getItemAmount(int i) { 
	return inventory[i]->getAmount(); 
}

// Intent: Get the amount of the item with specified id in the inventory
// Pre: id must be a valid option in ITEMID
// Post: Returns the amount of the item at with specified id in the inv
// \param id: Target's id
bool BackPack::getItemAmtById(int id) {
	// Seach in inventory
	for (size_t i = 0; i < inventory.size(); i++) {
		if (inventory[i]->getId() == id) {
			return true;
		}
	}

	return false;
}

// Intent: Earn money and add it to the current money amount
// Pre: amt must be a non-negative value
// Post: Adds the specified amount to the current money amount
// \param amt: earn money amount
void BackPack::earnMoney(int amt) {
	if (amt < 0) {
		// incMoney can't be negative
		return;
	}

	money += amt;
}

// Intent: Deduct money from the current money amount
// Pre: amt must be a non-negative value and money must be greater than or equal to amt
// Post: Deducts the specified amount from the current money amount
// \param amt: cost money amount
bool BackPack::costMoney(int amt) {
	if (amt < 0 || money < amt) {
		// costMoney can't be negative, deposite can't less than costMoney.
		return false; // money spent fail
	}

	money -= amt;
	return true; // money spent success
}

// Intent: Switch game status to backpack mode
// Pre: None
// Post: Sets the game status to backpack mode
void BackPack::invMode(void) {
	// init control variables
	curIndex = 0;
	curPage = 1;
	maxPage = ((int)inventory.size() - 1) / 8 + 1;

	GameManager::gameStatus = GAME_STATUS::BACKPACK;
}

// Intent: Move selection cursor up in the inventory
// Pre: None
// Post: Moves the selection cursor up in the inventory
void BackPack::chooseUp() {
	curIndex--;

	if (curIndex < 0) {
		curIndex = (int)inventory.size() - 1;
	}

	curPage = curIndex / 8 + 1;
}

// Intent: Move selection cursor down in the inventory
// Pre: None
// Post: Moves the selection cursor down in the inventory
void BackPack::chooseDown() {
	curIndex++;

	if (curIndex == inventory.size()) {
		curIndex = 0;
	}

	curPage = curIndex / 8 + 1;
}

// Intent: Use the currently selected item in the inventory
// Pre: None
// Post: Uses the currently selected item in the inventory
void BackPack::useItem(Role* curRole) 
{
	// inventory or current selected item is empty. use fail.
	if (inventory.empty() || !inventory[curIndex]->getAmount()) {
		return;
	}

	inventory[curIndex]->use(curRole);
	inventory[curIndex]->decAmount();

	if (inventory[curIndex]->getAmount() == 0 && inventory[curIndex]->getTag() == "Consumable") {
		delete inventory[curIndex];
		inventory[curIndex] = nullptr;
		inventory.erase(inventory.begin() + curIndex);

		curIndex = (curIndex - 1 < 0) ? 0 : curIndex - 1;
	}
}

// Intent: Use item in battle, may skip some options in bag
// Pre: target's id, who use it
// Post: Item be used by role
void BackPack::useItemById(Role* role, int id) {

	// The inventory loop check
	for (size_t i = 0; i < inventory.size(); i++) {
		if (inventory[i]->getId() == id) {
			inventory[i]->use(role);
			inventory[i]->decAmount();

			// Delete it if empty
			if (inventory[i]->getAmount() == 0 && inventory[i]->getTag() == "Consumable") {
				delete inventory[i];
				inventory[i] = nullptr;
				inventory.erase(inventory.begin() + i);
			}

			return;
		}
	}
}

// Intent: Equipment be destroy in combat, need to remove it from bag too
// Pre: target's id
// Post: Item be destroyed
void BackPack::deleteItemById(int id) {

	// Target item's id
	for (size_t i = 0; i < inventory.size(); i++) {
		if (inventory[i]->getId() == id) {
			inventory.erase(inventory.begin() + i);
			return;
		}
	}
}

// Intent: Close the backpack and switch back to map mode
// Pre: None
// Post: Sets the game status back to map mode
void BackPack::closeBag() {
	GameManager::gameStatus = GAME_STATUS::MAP;
}
