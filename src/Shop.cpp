#include "Shop.h"
#include "GameManager.h"
#include "Items.h"
#include "Role.h"
#include "Backpack.h"

Shop::Shop() {
    // wonderful shop sell everything!
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

    // woderful shop's stock of sale
    this->amountList[ITEMID::Godsbeard] = 3;
    this->amountList[ITEMID::GoldenRoot] = 3;
    this->amountList[ITEMID::TeleportScroll] = 2;
    this->amountList[ITEMID::Tent] = 2;
    this->amountList[ITEMID::WoodenSword] = 1;
    this->amountList[ITEMID::Hammer] = 1;
    this->amountList[ITEMID::MagicWand] = 1;
    this->amountList[ITEMID::Shoes] = 1;
    this->amountList[ITEMID::PlateArmor] = 1;
    this->amountList[ITEMID::Bracelet] = 1;

    this->chosenItemId = 0;
    this->curPage = 1;
    this->maxPage = (priceList.size() - 1) / 8 + 1;
    this->icon = '$';
}

void Shop::active(Role* role) {
    if (amountList[chosenItemId] == 0) {
        // The chosen item's stock is empty.
        return;
    }

    // cost money to buy, or can't afford the cost -> nothing happend.
    if (bag.costMoney(priceList[chosenItemId])) {
        std::string tag = (chosenItemId < ITEMID::WoodenSword) ? "Consumable" : "Equipment";

        bag.obtainItem(new Item(tag, ITEMID(chosenItemId)));
        amountList[chosenItemId]--;
    }
}

void Shop::chooseActiveUP() {
    chosenItemId--;

    if (chosenItemId < 0) {
        chosenItemId = ITEMID::Invalid - 1;
    }

    curPage = chosenItemId / 8 + 1;
}

void Shop::chooseActiveDown() {
    chosenItemId++;

    if (chosenItemId == ITEMID::Invalid) {
        chosenItemId = 0;
    }

    curPage = chosenItemId / 8 + 1;
}

vector<string> Shop::getAllChoose() {
    vector<string> itemList = getItemList();
    vector<string> vendorLists;

    vendorLists.push_back("Shop");

    for (int i = 0; i < ITEMID::Invalid; i++) {
        vendorLists.push_back(itemList[i] + ": " + to_string(priceList[i]) + "$  x" + to_string(amountList[i]));
    }

    return vendorLists;
}

int Shop::getChosenIndex() {
    return chosenItemId;
}