#include "Shop.h"
#include "GameManager.h"
#include "Items.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Constructor to initialize a shop with default prices, stock amounts, and other properties
// Pre: None
// Post: Initial the shop value
Shop::Shop()
{
    // Initialize prices for items in the shop
    this->priceList[int(ITEMID::Godsbeard)] = 10;
    this->priceList[int(ITEMID::GoldenRoot)] = 15;
    this->priceList[int(ITEMID::TeleportScroll)] = 30;
    this->priceList[int(ITEMID::Tent)] = 20;
    this->priceList[int(ITEMID::WoodenSword)] = 15;
    this->priceList[int(ITEMID::Hammer)] = 25;
    this->priceList[int(ITEMID::MagicWand)] = 15;
    this->priceList[int(ITEMID::Shoes)] = 18;
    this->priceList[int(ITEMID::PlateArmor)] = 23;
    this->priceList[int(ITEMID::Bracelet)] = 20;

    // Initialize stock amounts for items in the shop
    this->amountList[int(ITEMID::Godsbeard)] = 3;
    this->amountList[int(ITEMID::GoldenRoot)] = 3;
    this->amountList[int(ITEMID::TeleportScroll)] = 2;
    this->amountList[int(ITEMID::Tent)] = 2;
    this->amountList[int(ITEMID::WoodenSword)] = 1;
    this->amountList[int(ITEMID::Hammer)] = 1;
    this->amountList[int(ITEMID::MagicWand)] = 1;
    this->amountList[int(ITEMID::Shoes)] = 1;
    this->amountList[int(ITEMID::PlateArmor)] = 1;
    this->amountList[int(ITEMID::Bracelet)] = 1;

    // Initialize other properties of the shop
    this->chosenItemId = 0;
    this->icon = '$';
    this->tag = TAG_SHOP;
    this->description = "You can buy item in the shop.";
}

// Intent: Activate the shop when a player interacts with it
// Pre: The chosen item's stock must not be empty.
// Post: If the player can afford the item, it is obtained, and the item's stock amount decreases.
void Shop::active(Role* role) {

    // Check if the chosen item's stock is empty
    if (amountList[chosenItemId] == 0) 
    {
        return void();
    }

    // Check if the player can afford the chosen item
    if (bag.costMoney(priceList[chosenItemId])) {
        // Determine the tag based on the type of item
        std::string tag = (chosenItemId < int(ITEMID::WoodenSword)) ? "Consumable" : "Equipment";

        // Obtain the item from the shop and decrease its stock amount
        bag.obtainItem(new Item(tag, ITEMID(chosenItemId)));
        amountList[chosenItemId]--;
    }
}

// Intent: Move the selection of the active item in the shop upwards
// Pre: None
// Post: The selection of the active item is moved upwards
void Shop::chooseActiveUP() 
{
    // Move the selection upwards
    chosenItemId--; 

    // Wrap around if the selection goes below 0
    if (chosenItemId < 0) 
    {
        chosenItemId = int(ITEMID::Invalid) - 1;
    }
}

// Intent: Move the selection of the active item in the shop downwards
// Pre: None
// Post: The selection of the active item is moved downwards
void Shop::chooseActiveDown() 
{
    // Move the selection downwards
    chosenItemId++; 

    // Wrap around if the selection reaches the end of the list
    if (chosenItemId == int(ITEMID::Invalid))
    {
        chosenItemId = 0;
    }
}

// Intent: Get a list of all items in the shop along with their prices and stock amounts
// Pre: None
// Post: A vector containing strings representing each item, its price, and stock amount is returned
vector<string> Shop::getAllChoose() 
{
    vector<string> itemList = getItemList();    // Get a list of all items
    vector<string> vendorLists;                 // Initialize a vector to store the item information

    // Iterate through each item and add its information to the vendorLists vector
    for (int i = 0; i < int(ITEMID::Invalid); i++)
    {
        vendorLists.push_back(itemList[i] + ": " + to_string(priceList[i]) + "$  x" + to_string(amountList[i]));
    }

    // Return the list of item information
    return vendorLists; 
}

// Intent: Get the index of the currently chosen item in the shop
// Pre: None
// Post: The index of the currently chosen item is returned
int Shop::getChosenIndex() 
{
    return chosenItemId; 
}