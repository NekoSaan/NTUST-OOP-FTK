#pragma once
struct Point
{
	int y = -1;
	int x = -1;

	Point& operator = (Point pos);

	Point operator + (Point add);

	Point operator - (Point minus);
};

Point& Point::operator = (Point pos)
{
	this->x = pos.x;
	this->y = pos.y;
	return *this;
}

Point Point::operator + (Point add)
{
	return Point{ this->y + add.y , this->x + add.x };
}

Point Point::operator - (Point minus)
{
	return Point{ this->y - minus.y , this->x - minus.x };
}