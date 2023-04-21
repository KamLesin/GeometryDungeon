#pragma once

class Point
{
public:
	Point(double x, double y);
	Point();
	double x, y;
	Point operator+(const Point &a);
};

