#include "Shop.h"
#include "GameManager.h"
#include "Items.h"
#include "Role.h"
#include "Backpack.h"

Shop::Shop() {
    //wonderful shop sell everything!
    this->priceList[ITEMID::Godsbeard] = 10;
    this->priceList[ITEMID::GoldenRoot] = 15;
    this->priceList[ITEMID::TeleportScroll] = 30;
    this->priceList[ITEMID::Tent] = 20;
    this->priceList[ITEMID::WoodenSword] = 15;
    this->priceList[ITEMID::Hammer] = 25;
    this->priceList[ITEMID::MagicWand] = 15;
    this->priceList[ITEMID::Shoes] = 18;
    this->priceList[ITEMID::PlateArmor] = 23;
    this->priceList[ITEMID::Bracelet] = 20;

    //woderful shop only has two everything
    this->amountList[ITEMID::Godsbeard] = 2;
    this->amountList[ITEMID::GoldenRoot] = 2;
    this->amountList[ITEMID::TeleportScroll] = 2;
    this->amountList[ITEMID::Tent] = 2;
    this->amountList[ITEMID::WoodenSword] = 2;
    this->amountList[ITEMID::Hammer] = 2;
    this->amountList[ITEMID::MagicWand] = 2;
    this->amountList[ITEMID::Shoes] = 2;
    this->amountList[ITEMID::PlateArmor] = 2;
    this->amountList[ITEMID::Bracelet] = 2;

    this->chosenItemId = 0;
    this->icon = '$';
}

void Shop::active(Role* role) {
    if (bag.costMoney(priceList[chosenItemId]) && amountList[chosenItemId] > 0) {
        bag.obtainItem(new Item(ItemList[chosenItemId], ITEMID(chosenItemId)));
        amountList[chosenItemId]--;
    }
}

void Shop::chooseActiveUP() {
    chosenItemId--;
    if (chosenItemId < 0) {
        chosenItemId = ITEMID::Invalid - 1;
    }
}

void Shop::chooseActiveDown() {
    chosenItemId++;
    if (chosenItemId == ITEMID::Invalid) {
        chosenItemId = 0;
    }
}

vector<string> Shop::getAllChoose() {
    vector<string> itemNames;
    for (int i = 0; i < ITEMID::Invalid; i++) {
        itemNames.push_back(ItemList[i] + " $" + to_string(priceList[i]) + "  x" + to_string(amountList[i]));
    }

    return itemNames;
}

int Shop::getChosenIndex() {
    return chosenItemId;
}