#include "GamePch.h"


Point::Point()
{
}

void Point::Set(int x, int y)
{
	prevX = this->x;
	prevY = this->y;

	this->x = clamp(x, 0, gMap->GetWidth());
	this->y = clamp(y, 0, gMap->GetHeight());
}
