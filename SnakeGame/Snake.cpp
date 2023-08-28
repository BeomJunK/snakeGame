#include "GamePch.h"
#include "Snake.h"


#define Head GetHeadPoint()
#define Tail GetTailPoint()

Snake::Snake()
{
	int w = gMap->GetWidth();
	int h = gMap->GetHeight();

	moveSec = 1;
	lastMoveTime = 0;
	inputDir = moveDir = Direction::RIGHT;

	snakeList.push_back(new Point(w / 2, h / 2 , 0,0));

	
	snakePath.clear();
}

void Snake::Update(long elapsedTime)
{
	if (elapsedTime - lastMoveTime > moveSec)
	{
		lastMoveTime = elapsedTime;
		moveDir = inputDir;

		Move();
	}
}

void Snake::Move()
{
	gMap->UpdateCell(this);

	if (snakePath.empty())
		FindPath();

	int dir = static_cast<int>(moveDir);

	pathIndex++;

	//for AI
	for (int i = 0; i < 4; i++)
	{
		Point next = *Head + direction[i];
		if (snakePath.size() < 2)
			break;

		if (next == snakePath[pathIndex])
		{
			dir = i;
			break;
		}
	}

	Head->Set(Head->x + direction[dir].x, Head->y + direction[dir].y);

	FollowTail();

}

void Snake::ChangeDirection(Direction dir)
{
	if (inputDir == dir)
		return;

	//반대 방향으론 전환 불가
	if (moveDir == Direction::RIGHT && dir == Direction::LEFT
		|| moveDir == Direction::LEFT && dir == Direction::RIGHT)
		return;

	if (moveDir == Direction::UP && dir == Direction::DOWN
		|| moveDir == Direction::DOWN && dir == Direction::UP)
		return;

	inputDir = dir;
}

void Snake::AddTail()
{
	Point* p = new Point();

	p->Set(Tail->prevX, Tail->prevY);
	snakeList.push_back(p);
}

void Snake::FollowTail()
{
	//머리부분 밖에 없을땐 return
	if (snakeList.size() == 1)
		return;

	list<Point*>::iterator curIt = std::next(snakeList.begin(), 1);
	list<Point*>::iterator prevIt = snakeList.begin();
	for (; curIt != snakeList.end(); ++curIt)
	{
		(*curIt)->Set((*prevIt)->prevX, (*prevIt)->prevY);;

		prevIt = curIt;
	}
}

void Snake::FindPath()
{
	Point startPos = *Head;
	int w = gMap->GetWidth();
	int h = gMap->GetHeight();

	vector<vector<int>> pathCost = vector<vector<int>>(h, vector<int>(w, INT32_MAX));
	vector<vector<bool>> visitPath = vector<vector<bool>>(h, vector<bool>(w, false));

	visitPath[Head->y][Head->x] = true;
	pathCost[Head->y][Head->x] = 0;

	priority_queue<pair<int, Point>,vector<pair<int,Point>>, greater<pair<int, Point>>> pq;
	map<Point, Point> parent;
	pq.push(pair < int, Point>(0, *Head));

	Point preyPos = gMap->GetPreyPoint();
	Point _visit;
	while (pq.empty() == false)
	{
		Point next = pq.top().second;
		pq.pop();

		//4방향으로 방문
		for (int i = 0; i < 4; i++)
		{
			_visit = next + direction[i];

			//막힌 곳
			if (CanGo(_visit) == false)
				continue;
			//이미 갔던 곳
			if (visitPath[_visit.y][_visit.x])
				continue;
			visitPath[_visit.y][_visit.x] = true;
			
			int g = next.cost + moveCost[i];
			int h = 10 * (abs(preyPos.x - _visit.x) + abs(preyPos.y - _visit.y));
			int f = g + h;
			//이전에 코스트 더 적게 발견했던 곳
			if ( f > pathCost[_visit.y][_visit.x])
				continue;

			pq.push(pair<int, Point>(f, _visit));
			pathCost[_visit.y][_visit.x] = f;

			parent.insert(pair<Point,Point>(_visit, next));

			//도착지라면 중단
			if (_visit == preyPos)
				break;
		}
	}
	
	Point pos = preyPos;
	snakePath.clear();
	pathIndex = 0;
	while (true)
	{
		snakePath.push_back(pos);

		if (pos == startPos)
			break;

		pos = parent[pos];
	}

	::reverse(snakePath.begin(), snakePath.end());
}

bool Snake::CanGo(Point& p)
{
	int idx = static_cast<int>(moveDir);

	if (gMap->GetCellType(p) == CellType::Wall
		|| gMap->GetCellType(p) == CellType::Snake)
		return false;

	return true;
}
