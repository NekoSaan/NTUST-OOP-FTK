#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Role;

class Shop : public Object {
private:
    unordered_map<int, int> priceList;
    unordered_map<int, int> amountList;

    int chosenItemId;

public:
    Shop();

    // Object's virtual funtion
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();
};