#ifndef _BACKPACK_H_
#define _BACKPACK_H_

#include <string>
#include <vector>

// Declare Classes to let the file know there exists these two classes.
class Item; 
class Role;

// BackPack Class, for store item that player have
class BackPack {
private:
	// Storage
	int money;
	std::vector<Item*> inventory;

	// For display/use control
	int curIndex;
	int curPage;
	int maxPage;

public:
	// Default Constructor
	BackPack(void);

	// Obtain item, add it to bag
	void obtainItem(Item*);

	// Some getter
	int getMoney(void);
	int getCurIndex(void);
	int getCurPage(void);
	int getMaxPage(void);
	int getInventorySize(void);
	std::string getItemName(int);
	int getItemAmount(int);
	bool getItemAmtById(int);

	// Money
	void earnMoney(int);
	bool costMoney(int);

	// Control/Use
	void invMode(void);
	void chooseUp(); // input w
	void chooseDown(); // input s
	void useItem(Role*); // input enter
	void useItemById(Role*, int); // combat use
	void deleteItemById(int);
	void closeBag(); //input backspace
};

// Declare a global bag to let every file use, also prevent re-defined
extern BackPack bag; 

#endif // _BACKPACK_H_