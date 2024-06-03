#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration of Role class
class Role;

// Object class represents an object in the game world
class Object
{
public:
    // Constants for object tags
    static const string TAG_SHOP;
    static const string TAG_ENEMY;
    static const string TAG_EVENT;
    static const string TAG_TENT;

    // constructor
    Object();
    Object(char, int, int);

    // Set the position of the object
    void setPos(int, int);

    // getter
    // (y, x)
    pair<int, int> getPos();
    char getIcon();
    string getTag();

    // Start the active mode for the object
    void startActive();

    // Exit the active mode for the object
    void exitActive(Role* role);

    // virtual function
    virtual void active(Role* role) = 0; // Perform the active action for the object
    virtual void chooseActiveUP() = 0; // Move the selection cursor up in the active mode
    virtual void chooseActiveDown() = 0; // Move the selection cursor down in the active mode
    virtual vector<string> getAllChoose() = 0; // Get all the available choices in the active mode
    virtual int getChosenIndex() = 0; // Get the index of the currently chosen option in the active mode
    virtual vector<string> getDescription() = 0;

protected:
    string tag;                 // Tag identifying the object
    char icon;                  // Icon representing the object

    int y;                      // Y-coordinate of the object's position
    int x;                      // X-coordinate of the object's position

    virtual void exitActiveEvent(Role* role); //called when exitActive
};

#endif _OBJECT_H_