#include "View.h"

Point View::worldToScreen(Point p)
{
	Point ret = Point( scale * (p.x - center.x) + width / 2,  scale * (p.y  - center.y) + height / 2);
	return ret;
}
