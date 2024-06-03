#ifndef _EVENT_H_
#define _EVENT_H_
#include "Object.h"

class Event : public Object {
public:
    Event();

    // Object's virtual funtion
    void active(Role* role) override;
    void chooseActiveUP() override;
    void chooseActiveDown() override;
    vector<string> getAllChoose() override;
    int getChosenIndex() override;
    vector<string> getDescription() override;

protected:
    int usedFocus;
    int diceNum;
    int diceResult;
    int chosenIndex;
    bool hasActive;
    vector<string> description;

    void exitActiveEvent(Role* role) override;

    virtual void updateDescription() = 0;
    virtual void startEvent(Role* role) = 0;
};

#endif // _EVENT_H_
