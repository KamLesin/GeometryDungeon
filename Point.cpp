#include "Point.h"

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point Point::operator+(const Point& a)
{
	return Point(this->x + a.x, this->y + a.y);
}
