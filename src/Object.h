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

    // Default constructor
    Object();

    // Parameterized constructor
    Object(char, int, int);

    // Set the position of the object
    void setPos(int, int);

    // Get the position of the object
    pair<int, int> getPos();

    // Get the icon representing the object
    char getIcon();

    // Get the tag of the object
    string getTag();

    // Get the description of the object
    string getDescription();

    // Start the active mode for the object
    void startActive();

    // Exit the active mode for the object
    void exitActive();

    // Perform the active action for the object
    virtual void active(Role* role) = 0;

    // Move the selection cursor up in the active mode
    virtual void chooseActiveUP() = 0;

    // Move the selection cursor down in the active mode
    virtual void chooseActiveDown() = 0;

    // Get all the available choices in the active mode
    virtual vector<string> getAllChoose() = 0;

    // Get the index of the currently chosen option in the active mode
    virtual int getChosenIndex() = 0;

protected:
    string description = "";    // The description
    string tag;                 // Tag identifying the object
    char icon;                  // Icon representing the object

    int y;                      // Y-coordinate of the object's position
    int x;                      // X-coordinate of the object's position
};

#endif _OBJECT_H_