#pragma once
#include "GamePch.h"
#include "Cell.h"
#include "Point.h"

using namespace std;

class Snake;

class GameMap
{
public:
	GameMap(int width, int height, int borderSize);

public:
	void Draw();
	void Clear(bool allClear = false);
	void Reset();

	CellType GetCellType(Point& p) { return gameMap[p.y][p.x]->GetCellType(); }
	void SetCellType(const Point& p, CellType type) { gameMap[p.y][p.x]->SetCellType(type); }
	void UpdateCell(Snake* snake);
	void SpawnPrey();
	Point& GetPreyPoint();
	Point& GetPrevPreyPoint();
	void SpawnX2();

	int GetWidth() { return width; }
	int GetHeight() { return height; }

protected:
	int width;
	int height;
	int borderSize;

	Point preyPos;
	Point prevPreyPos;

	inline bool IsEmptyCell(int x, int y);

private:
	void SetColor(unsigned short text){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);}

private:
	vector<vector<Cell*>> gameMap;
	queue<int> preySpawnSchedul;
	//ÄÜ¼ÖÃ¢¿¡ ÂïÀ» ¸Êstring
	string mapStr;

};

