#ifndef _SHOP_H_
#define _SHOP_H_

#include <unordered_map>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

// Forward declaration
class Role;

// Shop class represents a shop object in the game
class Shop : public Object 
{
private:
    unordered_map<int, int> priceList;  // Mapping from item ID to its price
    unordered_map<int, int> amountList; // Mapping from item ID to its available amount
    int chosenItemId;                   // ID of the item chosen by the player

public:
    // Constructor for Shop class
    Shop();

    // Object's virtual funtion
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();
    vector<string> getDescription();
};

#endif _SHOP_H_