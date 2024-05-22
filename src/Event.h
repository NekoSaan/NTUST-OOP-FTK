#ifndef _EVENT_H_
#define _EVENT_H_
#include "Object.h"
class Object;
class Event : public Object 
{
public:
    Event();

    // Object's virtual funtion
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();

protected:
    int usedFocus;
    int diceNum;
    int chosenIndex;
    bool hasActive;

    virtual void startEvent(Role* role) = 0;
};

#endif // _EVENT_H_