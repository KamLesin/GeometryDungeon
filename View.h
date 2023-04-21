#pragma once
#include "Point.h"

// used to move camera
class View
{
public:
	Point center;
	double scale;
	double height, width;
	Point worldToScreen(Point p);
};
