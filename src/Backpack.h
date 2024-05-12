#ifndef _BACKPACK_H_
#define _BACKPACK_H_
#include "Items.h"
#include "GameManager.h"

class BackPack {
private:
	int money;
	std::vector<Item*> inventory;

public:
	BackPack(void);

	void obtainItem(Item*);

	int getMoney(void);

	void earnMoney(int);

	bool costMoney(int);

	// void invMode(Role*); true
	void invMode(void);
};

BackPack::BackPack(void) : money(600) {
	// Initial Supplies or nothing
	for (int i = 0; i < ITEMID::WoodenSword; i++) {
		Item* newItem = new Item("Consumable", ITEMID(i));
		obtainItem(newItem);
	}
}

void BackPack::obtainItem(Item* item) {
	if (item->getId() > ITEMID::Tent) {
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
	int curIndex = 0;
	int curPage = 1, maxPage = ((int) inventory.size() - 1) / 8 + 1;

	double startT = clock();
	double endT = clock();

	do
	{
		// Compute the time lap
		double timeFrame = (endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= GTIMELOG)
		{
			if (gKeyState[int(VALIDINPUT::EW)]) {
				curIndex -= (curIndex > 0) ? 1 : 0;
			}
			else if (gKeyState[int(VALIDINPUT::ES)]) {
				curIndex += (curIndex < inventory.size() - 1) ? 1 : 0;
			}
			else if (gKeyState[int(VALIDINPUT::EENTER)] && !inventory.empty()) {
				// inventory[curIndex]->use(curRole);
				inventory[curIndex]->decAmount();

				if (inventory[curIndex]->getAmount() == 0 && inventory[curIndex]->getTag() == "Consumable") {
					inventory[curIndex] = nullptr;
					delete inventory[curIndex];
					inventory.erase(inventory.begin() + curIndex);

					curIndex = max(0, curIndex - 1);
				}
			}

			curPage = curIndex / 8 + 1;

			startT = clock();
		}

		outputInformation();

		vector<string> information;
		information.push_back("Bag (Page:" + to_string(curPage) + "/" + to_string(maxPage) + ")");

		for (int i = (curPage - 1) * 8; i < curPage * 8; i++) {
			if (i >= inventory.size()) {
				information.push_back(" ");
				continue;
			}

			if (curIndex == i) {
				information.push_back("-> " + inventory[i]->getName() + ": " + to_string(inventory[i]->getAmount()));
			}
			else {
				information.push_back("   " + inventory[i]->getName() + ": " + to_string(inventory[i]->getAmount()));
			}
		}

		information.push_back(" "); // seperate by 1 line
		information.push_back("___________Item Description__________");
		information.push_back("To be countinue");

		informationShow(information);

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EBACKSPACE)]);
}

static BackPack bag;

#endif // _BACKPACK_H_