#include "Event.h"
#include "Role.h"

// Intent: Initializes the Event object with default values.
// Pre: None.
// Post: Event object is initialized with default values.
Event::Event() 
{
    this->usedFocus = 0;
    this->chosenIndex = 0;
    this->diceNum = 3;
    this->hasActive = false;
    this->icon = '?';
    this->tag = TAG_EVENT;
    this->description = "Random thing will happen.";
}

// Intent: Activate the event based on the chosen index.
// Pre: A Role object must be provided.
// Post: The event is activated, modifying the Role object accordingly.
void Event::active(Role* role) 
{    
    switch (chosenIndex) 
    {
    case 0:
        startEvent(role);
        break;
    case 1:
        usedFocus++;
        if (usedFocus > diceNum) usedFocus = diceNum;
        if (usedFocus > role->getFocus()) usedFocus = role->getFocus();
        break;
    case 2:
        usedFocus--;
        if (usedFocus < 0) usedFocus = 0;
        break;
    case 3:
        exitActive();
    }
}

// Intent: Move the selection cursor up.
// Pre: None.
// Post: The selection cursor is moved up.
void Event::chooseActiveUP() 
{
    chosenIndex--;

    if (chosenIndex < 0) 
    {
        chosenIndex = 3;
    }
}

// Intent: Move the selection cursor down.
// Pre: None.
// Post: The selection cursor is moved down.
void Event::chooseActiveDown() 
{
    chosenIndex++;

    if (chosenIndex > 3) 
    {
        chosenIndex = 0;
    }
}

// Intent: Get all available choices for the event.
// Pre: None.
// Post: Returns a vector containing all available choices.
vector<string> Event::getAllChoose() 
{
    vector<string> choose;
    choose.push_back("Do it!");
    choose.push_back("Increase focus");
    choose.push_back("Decrease focus");
    choose.push_back("Go back");
    return choose;
}

// Intent: Get the index of the chosen action.
// Pre: None.
// Post: Returns the index of the chosen action.
int Event::getChosenIndex() 
{    
    return chosenIndex;
}