#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "Object.h"
#include "Items.h"

using namespace std;

class Shop : public Object {
private:
    unordered_map<int, int> priceList;
    int chosenItemId;

public:
    Shop();

    void startActive(); //tell game need to display choose screen
    //void active(Role* role);
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

    this->chosenItemId = 0;
}

void Shop::startActive(){
    //not finish
}

void Shop::active(Role* role){
    //not finish
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

vector<string> getAllChoose(){
    vector<string> itemNames;
    for(int i = 0; i < ITEMID::Invalid; i++){
        itemNames.push_back(ItemList[i]);
    }

    return itemNames;
}
