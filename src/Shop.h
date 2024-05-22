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

    // Trigger the shop's interaction with a role
    void active(Role* role);

    // Choose the next active item in the shop
    void chooseActiveUP();

    // Choose the previous active item in the shop
    void chooseActiveDown();

    // Get all possible choices for the shop's actions
    vector<string> getAllChoose();

    // Get the index of the chosen action
    int getChosenIndex();
};

#endif _SHOP_H_