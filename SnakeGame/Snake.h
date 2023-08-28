#pragma once
#include "GamePch.h"

class Snake
{
public:
	Snake();

	void Update(long elapsedTime);
	void Move();
	void FindPath();

	void ChangeDirection(Direction dir);
	void ClearPath() { snakePath.clear(); }
	inline long GetMoveSec() { return moveSec; }
	inline void SetMoveSec(long sec) { moveSec = sec; }
	inline Point* GetHeadPoint() { return snakeList.front(); }
	inline Point* GetTailPoint() { return snakeList.back(); }
	inline list<Point*> GetSnake() { return snakeList; }

	
	void AddTail();
protected:
	void FollowTail();

	bool CanGo(Point& p);

	Direction inputDir;
	Direction moveDir;

	long moveSec;
	long lastMoveTime;

	list<Point*> snakeList;

	int pathIndex = 0;
	vector<Point> snakePath;


	Point direction[4] =
	{
		Point { -1 , 0 ,0, 0},
		Point { 0 , -1 ,0, 0},
		Point { 1 , 0 ,0, 0},
		Point { 0 , 1 ,0, 0},
	};
	int moveCost[4] =
	{
		10,//LEFT
		10,//DOWN
		10,//RIGHT
		10,//UP
	};

};

