#ifndef _BACKPACK_H_
#define _BACKPACK_H_
#include <string>
#include <vector>

class Item;
class Role;

class BackPack {
private:
	int money;
	std::vector<Item*> inventory;

	int curIndex;
	int curPage;
	int maxPage;

public:
	BackPack(void);

	void obtainItem(Item*);

	//some getter, maybe too more
	int getMoney(void);
	int getCurIndex();
	int getCurPage();
	int getMaxPage();
	int getInventorySize();
	std::string getItemName(int i);
	int getItemAmount(int i);

	void earnMoney(int);

	bool costMoney(int);

	// void invMode(Role*); true
	void invMode(void);
	void chooseUp(); //input w
	void chooseDown(); //input s
	void useItem(Role*); //input enter
	void closeBag(); //input backspace
};

extern BackPack bag;

#endif // _BACKPACK_H_