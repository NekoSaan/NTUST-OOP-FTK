#ifndef _POINT_H_
#define _POINT_H_

struct Point
{
	// The y and x
	int y = -1;
	int x = -1;

	// Operator give value
	Point& operator = (Point pos);

	// Operator addation
	Point operator + (Point add);

	// Operator minus
	Point operator - (Point minus);

	// Operator compare equal
	bool operator == (Point equal);
};

#endif // _POINT_H_