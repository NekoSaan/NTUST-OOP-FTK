#include "ChestEvent.h"
#include "dice.h"
#include "Role.h"
#include "Backpack.h"

// Intent: Constructor for the ChestEvent class initializing member variables
// Pre: None
// Post: Initializes the member variables for a new ChestEvent instance
ChestEvent::ChestEvent(void)
{
    // initialize the variable
    this->usedFocus = 0;
    this->chosenIndex = 0;
    this->diceNum = 3;
    this->hasActive = false;
    this->icon = '?';
    this->tag = TAG_EVENT;

    // Initialize description
    updateDescription();
}

// Intent: Update the description of the chest event based on the current state
// Pre: None
// Post: Updates the description vector with appropriate messages based on whether the event is active and the dice result
void ChestEvent::updateDescription() {
    if (hasActive == false) {
        // Initial descriptions before the event starts
        description.clear();
        description.push_back("Do you want to open the chest ?");
        description.push_back("hit 3 get $100 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 3, 50)) + ")");
        description.push_back("hit 2 get $20 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 2, 50)) + ")");
        description.push_back("hit 1 get $5 (" + formatProbability(getExpectProbability(usedFocus, diceNum, 1, 50)) + ")");
        description.push_back("hit 0 get 10 damage (" + formatProbability(getExpectProbability(usedFocus, diceNum, 0, 50)) + ")");
        description.push_back("Used focus: " + to_string(usedFocus));
    }
    else if (diceResult == 3) {
        // Description when dice result is 3
        description.clear();
        description.push_back("You open the chest.");
        description.push_back("3 You get $100!");
    }
    else if (diceResult == 2) {
        // Description when dice result is 2
        description.clear();
        description.push_back("You open the chest.");
        description.push_back("2 You get $20!");
    }
    else if (diceResult == 1) {
        // Description when dice result is 1
        description.clear();
        description.push_back("You open the chest.");
        description.push_back("1 You get $5!");
    }
    else if (diceResult == 0) {
        // Description when dice result is 0
        description.clear();
        description.push_back("It is a trap");
        description.push_back("0 You get 10 damage!");
    }
}

// Intent: Start the chest event, roll dice and update the role's status based on the result
// Pre: role must be a valid pointer to a Role object
// Post: Updates the role's focus and health based on the dice result, and sets the hasActive flag to true
void ChestEvent::startEvent(Role* role)
{
    diceResult = dice(usedFocus, diceNum, 50);
    role->setFocus(role->getFocus() - usedFocus);

    switch (diceResult)
    {
    case 3:
        // Reward for dice result 3
        bag.earnMoney(100);
        break;
    case 2:
        // Reward for dice result 2
        bag.earnMoney(20);
        break;
    case 1:
        // Reward for dice result 1
        bag.earnMoney(5);
        break;
    case 0:
        // Penalty for dice result 0
        role->setHp(role->getHp() - 10);
    }

    hasActive = true;
}
