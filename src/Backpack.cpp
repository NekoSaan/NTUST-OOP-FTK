#include "Backpack.h"
#include "Items.h"
#include "GameManager.h"

BackPack bag;

// Intent: Class constructor
// Pre: None
// Post: Constructs a BackPack object with an initial money value of 600 and initializes inventory with default items.
BackPack::BackPack(void) : money(600)
{
	// Initial Supplies or nothing
	for (int i = 0; i < (int)ITEMID::WoodenSword; i++) 
	{
		obtainItem(new Item("Consumable", ITEMID(i)));
	}
}

// Intent: Add an item to the inventory
// Pre: item must be a valid pointer to an Item object
// Post: Adds the item to the inventory or increments its amount if it already exists in the inventory
void BackPack::obtainItem(Item* item) 
{
	if (item->getId() > (int)ITEMID::Tent) 
	{
		inventory.push_back(item);
		return;
	}

	for (int i = 0; i < inventory.size(); i++) 
	{
		if (item->getId() == inventory[i]->getId()) 
		{
			inventory[i]->incAmount();

			item = nullptr;
			delete item;
			return;
		}
	}

	inventory.push_back(item);
}

// Intent: Get the current amount of money
// Pre: None
// Post: Returns the amount of money in the backpack
int BackPack::getMoney(void) 
{
	return money;
}

// Intent: Get the current index in the inventory
// Pre: None
// Post: Returns the current index in the inventory
int BackPack::getCurIndex() 
{
	return curIndex;
}

// Intent: Get the current page in the inventory
// Pre: None
// Post: Returns the current page in the inventory
int BackPack::getCurPage() 
{
	return curPage;
}

// Intent: Get the maximum page in the inventory
// Pre: None
// Post: Returns the maximum page in the inventory
int BackPack::getMaxPage() 
{
	return maxPage;
}

// Intent: Get the size of the inventory
// Pre: None
// Post: Returns the size of the inventory
int BackPack::getInventorySize() 
{
	return (int)inventory.size();
}

// Intent: Get the name of the item at the specified index in the inventory
// Pre: i must be a valid index within the inventory range
// Post: Returns the name of the item at the specified index in the inventory
std::string BackPack::getItemName(int i) 
{
	return inventory[i]->getName();
}

// Intent: Get the amount of the item at the specified index in the inventory
// Pre: i must be a valid index within the inventory range
// Post: Returns the amount of the item at the specified index in the inventory
int BackPack::getItemAmount(int i) 
{
	return inventory[i]->getAmount();
}

// Intent: Earn money and add it to the current money amount
// Pre: amt must be a non-negative value
// Post: Adds the specified amount to the current money amount
void BackPack::earnMoney(int amt) 
{
	if (amt < 0) 
	{
		// incMoney can't be negative
		return;
	}

	money += amt;
}

// Intent: Deduct money from the current money amount
// Pre: amt must be a non-negative value and money must be greater than or equal to amt
// Post: Deducts the specified amount from the current money amount
bool BackPack::costMoney(int amt) 
{
	if (amt < 0 || money < amt) 
	{
		// costMoney can't be negative, deposite can't less than costMoney.
		return false; // money spent fail
	}

	money -= amt;
	return true; // money spent success
}

// Intent: Switch game status to backpack mode
// Pre: None
// Post: Sets the game status to backpack mode
void BackPack::invMode(void) 
{
	curIndex = 0;
	curPage = 1;
	maxPage = ((int)inventory.size() - 1) / 8 + 1;

	GameManager::gameStatus = GAME_STATUS::BACKPACK;
}

// Intent: Move selection cursor up in the inventory
// Pre: None
// Post: Moves the selection cursor up in the inventory
void BackPack::chooseUp() 
{
	curIndex--;

	if (curIndex < 0) 
	{
		curIndex = (int)inventory.size() - 1;
	}

	curPage = curIndex / 8 + 1;
}

// Intent: Move selection cursor down in the inventory
// Pre: None
// Post: Moves the selection cursor down in the inventory
void BackPack::chooseDown() 
{
	curIndex++;

	if (curIndex == inventory.size()) 
	{
		curIndex = 0;
	}

	curPage = curIndex / 8 + 1;
}

// Intent: Use the currently selected item in the inventory
// Pre: None
// Post: Uses the currently selected item in the inventory
void BackPack::useItem() 
{
	// inventory or current selected item is empty. use fail.
	if (inventory.empty() || !inventory[curIndex]->getAmount()) 
	{
		return;
	}

	// inventory[curIndex]->use(curRole);
	inventory[curIndex]->decAmount();

	if (inventory[curIndex]->getAmount() == 0 && inventory[curIndex]->getTag() == "Consumable") 
	{
		inventory[curIndex] = nullptr;
		delete inventory[curIndex];
		inventory.erase(inventory.begin() + curIndex);

		curIndex = (curIndex - 1 < 0) ? 0 : curIndex - 1;
	}
}

// Intent: Close the backpack and switch back to map mode
// Pre: None
// Post: Sets the game status back to map mode
void BackPack::closeBag() 
{
	GameManager::gameStatus = GAME_STATUS::MAP;
}
