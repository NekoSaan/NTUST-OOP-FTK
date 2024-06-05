#ifndef _EVENT_H_
#define _EVENT_H_

#include "Object.h"

// Event Class, inherti Object Class
class Event : public Object {
public:
    // Default Constructor
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

    // Exit active mode
    void exitActiveEvent(Role* role) override;

    // Virtual function that update the info that event provide
    virtual void updateDescription() = 0;
    virtual void startEvent(Role* role) = 0;
};

#endif // _EVENT_H_