#include "Event.h"
#include "Role.h"
#include "GameManager.h"
#include "Rect.h"

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
}

// Intent: Activate the event based on the chosen index.
// Pre: A Role object must be provided.
// Post: The event is activated, modifying the Role object accordingly.
void Event::active(Role* role)
{
    switch (chosenIndex)
    {
    case 0: // do it
        if (!hasActive) {
            startEvent(role);
            usedFocus = 0;
        }

        break;
    case 1: // increase focus
        usedFocus = min(diceNum, min(role->getFocus(), usedFocus + 1));
        break;
    case 2: // decrease focus
        usedFocus = max(0, usedFocus - 1);
        break;
    case 3: // go back
        exitActive(role);
        break;
    }

    updateDescription();
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

vector<string> Event::getDescription() {
    return description;
}

void Event::exitActiveEvent(Role* role) {
    if (hasActive) {
        GameManager::gameBoard[role->getPos().first][role->getPos().second].setObject(NULL);
        return;
    }
}