#ifndef _TENT_H_
#define _TENT_H_

#include "Object.h"
#include "Rect.h"

class Tent : public Object {

private:
    int cd;             // Tent cd time
    int chosenIndex;    // In list been chosen index
    Rect* rect;         // Rect

public:
    // Construct
    Tent(Rect*);

    // The notify functiobn
    void notify();

    //Object's virtual function
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();
    vector<string> getDescription();
};

#endif // _TENT_H_