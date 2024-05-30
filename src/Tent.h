#pragma once
#include "Object.h"
#include "Rect.h"

class Tent : public Object {
private:
    int cd;
    int chosenIndex;
    Rect* rect;

public:
    Tent(Rect*);

    void notify();

    //Object's virtual function
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();
    vector<string> getDescription();
};