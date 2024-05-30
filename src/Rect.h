#ifndef _RECT_H_
#define _RECT_H_

#include <utility> 

// Forward declaration
class Object;

// Rect class represents a rectangular area in the game environment
class Rect
{
public:
    // Constructor for Rect class
    Rect();

    // Get the icon of the Rect
    std::pair<char, int> getIcon();

    // Set the visibility status of the Rect
    void setIsVisible(bool visible);

    // Set the passability status of the Rect
    void setCanPass(bool b);

    // Set the object associated with the Rect
    void setObject(Object* o);

    // Get the visibility status of the Rect
    bool getIsVisible();

    // Get the passability status of the Rect
    bool getCanPass();

    // Get the object associated with the Rect
    Object* getObject();

    bool die;
    void setBeSelect(bool b);
    bool getBeSelect();

private:
    bool isVisible; // Visibility status of the Rect
    bool canPass;   // Passability status of the Rect
    bool beSelect;
    Object* object; // Object associated with the Rect
};

#endif _RECT_H_
