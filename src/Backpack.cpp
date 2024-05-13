#include "Backpack.h"
#include "Items.h"
#include "GameManager.h"

BackPack bag;

BackPack::BackPack(void) : money(600) {
	// Initial Supplies or nothing
	for (int i = 0; i < (int)ITEMID::WoodenSword; i++) {
		Item* newItem = new Item("Consumable", ITEMID(i));
		obtainItem(newItem);
	}
}

void BackPack::obtainItem(Item* item) {
	if (item->getId() > (int)ITEMID::Tent) {
		inventory.push_back(item);
		return;
	}

	for (int i = 0; i < inventory.size(); i++) {
		if (item->getId() == inventory[i]->getId()) {
			inventory[i]->incAmount();

			item = nullptr;
			delete item;
			return;
		}
	}

	inventory.push_back(item);
}

int BackPack::getMoney(void) {
	return money;
}

int BackPack::getCurIndex() {
	return curIndex;
}

int BackPack::getCurPage() {
	return curPage;
}

int BackPack::getMaxPage() {
	return maxPage;
}

int BackPack::getInventorySize() {
	return inventory.size();
}

std::string BackPack::getItemName(int i) {
	return inventory[i]->getName();
}

int BackPack::getItemAmount(int i) {
	return inventory[i]->getAmount();
}

void BackPack::earnMoney(int amt) {
	if (amt < 0) {
		// incMoney can't be negative
		return;
	}

	money += amt;
}

bool BackPack::costMoney(int amt) {
	if (amt < 0 || money < amt) {
		// costMoney can't be negative, deposite can't less than costMoney.
		return false; // money spent fail
	}

	money -= amt;
	return true; // money spent success
}

void BackPack::invMode(void) {
	curIndex = 0;
	curPage = 1;
	maxPage = ((int)inventory.size() - 1) / 8 + 1;

	GameManager::gameStatus = GAME_STATUS::BACKPACK;
}

void BackPack::chooseUp() {
	curIndex -= (curIndex > 0) ? 1 : 0;
}
void BackPack::chooseDown() {
	curIndex += (curIndex < inventory.size() - 1) ? 1 : 0;
}

void BackPack::useItem() {
	if (inventory.empty()) {
		return; // inventory is empty, there is no item for use
	}

	// inventory[curIndex]->use(curRole);
	inventory[curIndex]->decAmount();

	if (inventory[curIndex]->getAmount() == 0 && inventory[curIndex]->getTag() == "Consumable") {
		inventory[curIndex] = nullptr;
		delete inventory[curIndex];
		inventory.erase(inventory.begin() + curIndex);

		curIndex = max(0, curIndex - 1);
	}
}

void BackPack::closeBag() {
	GameManager::gameStatus = GAME_STATUS::MAP;
}