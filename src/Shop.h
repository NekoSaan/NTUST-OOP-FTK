#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "Object.h"
#include "Items.h"
#include "Role.h"
#include "Backpack.h"

using namespace std;

class Shop : public Object {
private:
    unordered_map<int, int> priceList;
    int chosenItemId;

public:
    Shop();

    void startActive(); //tell game need to display choose screen
    void active(Role*);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
};


//put into .cpp when everything done
Shop::Shop(){
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

    this->chosenItemId = 0;
}

void Shop::startActive(){
    //not finish
}

void Shop::active(Role* role){
    if (bag.costMoney(priceList[chosenItemId])) {
        bag.obtainItem(new Item(ItemList[chosenItemId], ITEMID(chosenItemId)));
    }
}

void Shop::chooseActiveUP(){
    chosenItemId--;
    if(chosenItemId < 0){
        chosenItemId = ITEMID::Invalid - 1;
    }
}

void Shop::chooseActiveDown(){
    chosenItemId++;
    if(chosenItemId == ITEMID::Invalid){
        chosenItemId = 0;
    }
}

vector<string> Shop::getAllChoose(){
    vector<string> itemNames;
    for(int i = 0; i < ITEMID::Invalid; i++){
        itemNames.push_back(ItemList[i] + " $" + to_string(priceList[i]));
    }

    return itemNames;
}