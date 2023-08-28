#pragma once
class Point
{

public:
	Point();
	Point(int x, int y) : x(x), y(y){}
	Point(int x, int y, int prevX, int prevY)  : x(x), y(y), prevX(prevX), prevY(prevY) {}

	int x;
	int y;

	int prevX;
	int prevY;

	int cost = 0;

	void Set(int x, int y);


	Point operator+(Point& other)
	{
		Point p = { other.x + x, other.y + y , 0 , 0};
		return p;
	}
	bool operator==(Point& other)
	{
		return other.x == x && other.y == y;
	}
	bool operator<(const Point& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}
};

