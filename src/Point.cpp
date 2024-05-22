#include "Point.h"

// Intent: Assign the coordinates of one Point to another
// Pre: Parameter pos is a valid Point object
// Post: Assigns the coordinates of pos to the current Point object and returns a reference to the current object
inline Point& Point::operator = (Point pos)
{
    this->x = pos.x;
    this->y = pos.y;
    return *this;
}

// Intent: Add the coordinates of two Points
// Pre: Parameter add is a valid Point object
// Post: Returns a new Point object with coordinates equal to the sum of the coordinates of the current Point and add
inline Point Point::operator + (Point add)
{
    return Point{ this->y + add.y , this->x + add.x };
}

// Intent: Subtract the coordinates of one Point from another
// Pre: Parameter minus is a valid Point object
// Post: Returns a new Point object with coordinates equal to the difference of the coordinates of the current Point and minus
inline Point Point::operator - (Point minus)
{
    return Point{ this->y - minus.y , this->x - minus.x };
}

// Intent: Check if two Points have the same coordinates
// Pre: Parameter equal is a valid Point object
// Post: Returns true if the coordinates of the current Point and equal are equal, false otherwise
inline bool Point::operator == (Point equal)
{
    return (this->y == equal.y && this->x == equal.x);
}
