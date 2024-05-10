#ifndef _BACKPACK_H_
#define _BACKPACK_H_
#include "Items.h"
#include "GameManager.h"
#include "Main.h"

class BackPack {
private:
	int money;
	std::vector<Item*> inventory;

public:
	BackPack(void);

	void obtainItem(Item*);

	void invMode(void);
};

BackPack::BackPack(void) : money(600) {
	// Initial Supplies or nothing
	Item* godsBeard = new Item("cosumer", ITEMID::Godsbeard);
	obtainItem(godsBeard);
	obtainItem(godsBeard);

	for (int i = 0; i < 8; i++) {
		Item* dummyItem = new Item("dummyItem", ITEMID::Invalid);
		obtainItem(dummyItem);
	}
}

void BackPack::obtainItem(Item* item) {
	if (item->getId() > ITEMID::Tent) {
		inventory.push_back(item);
		return;
	}

	for (int i = 0; i < inventory.size(); i++) {
		if (item->getId() == inventory[i]->getId()) {
			inventory[i]->amount++;
			return;
		}
	}

	inventory.push_back(item);
}

void BackPack::invMode(void) {
	int curIndex = 0;
	int curPage = 1, maxPage = (inventory.size() - 1) / 8 + 1;

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

			curPage = curIndex / 8 + 1;

			startT = clock();
		}

		outputInformation();

		vector<string> information;
		information.push_back("Bag (Page:" + to_string(curPage) + "/" + to_string(maxPage) + ")");
		int lastItem = min(inventory.size(), curPage * 8);

		for (int i = (curPage - 1) * 8; i < lastItem; i++) {
			if (curIndex == i) {
				information.push_back("-> " + inventory[i]->getName() + ": " + to_string(inventory[i]->amount));
			}
			else {
				information.push_back("   " + inventory[i]->getName() + ": " + to_string(inventory[i]->amount));
			}
		}

		information.push_back(" "); // seperate by 1 line
		information.push_back("___________Item Description__________");
		information.push_back("To be countinue");

		informationShow(information);

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	} while (!gKeyState[int(VALIDINPUT::EESC)]);
}

static BackPack bag;

#endif // _BACKPACK_H_