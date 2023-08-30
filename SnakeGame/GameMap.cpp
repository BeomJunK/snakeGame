#include"GamePch.h"
#include "Cell.h"
#include "GameManager.h"
#include "Snake.h"
#include "GameMap.h"

GameMap::GameMap(int width, int height, int borderSize)
{
	this->width = width;
	this->height = height;
	this->borderSize = borderSize;

	//창크기를 맵크기에 맞게 설정
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	std::string str = "MODE CON COLS=" + std::to_string(width * 2) + " LINES=" + std::to_string(height);
	system(str.c_str());

	//map init
	gameMap.resize(height);
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			gameMap[h].push_back(new Cell());
		}
	}

	Clear(true);
}

void GameMap::Draw()
{
	string wall = "* ";
	string prey = "ⓖ";
	string snake = "▩";
	string x2 = "x2";

	string tempMapStr = "";

	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			CellType type = gameMap[h][w]->GetCellType();
			switch (type)
			{
				case CellType::Empty:
				{
					tempMapStr.append("  ");
				}
				break;

				case CellType::Wall:
				{
					tempMapStr.append(wall);
				}
				break;
				case CellType::Prey:
				{
					tempMapStr.append(prey);
				}
				break;
				case CellType::X2:
					tempMapStr.append(x2);
					break;
				case CellType::Snake:
					tempMapStr.append(snake);
					break;
			}
		}
	}

	if (mapStr.compare(tempMapStr) == 0)
		return;

	mapStr = tempMapStr;
	SetColor(static_cast<short>(Color::Green));
	cout << mapStr;
	SetColor(static_cast<short>(Color::WHITE));
}

void GameMap::Clear(bool allClear)
{
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (((w < borderSize || w >= width - borderSize) || h < borderSize || h >= height - borderSize))
				gameMap[h][w]->SetCellType(CellType::Wall);
			else if ( !allClear && (gameMap[h][w]->GetCellType() == CellType::Prey || gameMap[h][w]->GetCellType() == CellType::X2))
				continue;
			else
				gameMap[h][w]->SetCellType(CellType::Empty);
		}
	}
}

void GameMap::Reset()
{
	queue<int> empty;
	swap(preySpawnSchedul, empty);
	Clear(true);
	SpawnPrey();
}

void GameMap::UpdateCell(Snake* snake)
{
	Clear();
	GameManager& mgr = GameManager::getInstance();

	

	
	//머리부분 이동된 이벤트 처리
	Point* head = snake->GetHeadPoint();
	switch (gameMap[head->y][head->x]->GetCellType())
	{
		case CellType::Prey:
		{
			snake->AddTail();
			preySpawnSchedul.push(mgr.GetCurrentPreySpawnRate());
			mgr.ResetSpawnRate();
			mgr.AddCurrentGameScore(mgr.GetPrevScore());

			const long MIN_MOVE_SEC = 1;
			long newMoveSec = snake->GetMoveSec() - 20;
			long moveSec = clamp(newMoveSec, MIN_MOVE_SEC, snake->GetMoveSec());
			snake->SetMoveSec(moveSec);

			//일정확률 먹이 2배
			//SpawnX2();
		}
		break;
		case CellType::X2:
		{
			mgr.MultiflySpawnRate(2);
		}
		break;
		case CellType::Wall:
		case CellType::Snake:
		{
			mgr.SetCurrentGameState(GameState::End);
		}
		break;
	}
	//머리 이동 Update
	gameMap[head->y][head->x]->SetCellType(CellType::Snake);
	auto snakeList = snake->GetSnake();
	list<Point*>::iterator it = snakeList.begin();
	//꼬리 이동 Update
	++it;
	for (; it != snakeList.end(); ++it)
	{
		gameMap[(*it)->y][(*it)->x]->SetCellType(CellType::Snake);
	}


	//Prey Schedul..
	//!!!스케줄링을 하지않고 그냥 스폰하게되면 머리부분과 먹이가 겹치게 스폰될시 Snake로 바꿔버린다.
	while (!preySpawnSchedul.empty())
	{
		for (int i = 0; i < preySpawnSchedul.front(); ++i)
		{
			SpawnPrey();
		}
		preySpawnSchedul.pop();
	}
}

void GameMap::SpawnPrey()
{
	vector<pair<int, int>> emptyCells;

	//먹이를 소환할수 있는곳 찾기
	for(int y = 0; y<height; ++y)
		for (int x = 0; x < width; ++x)
		{
			if (IsEmptyCell(x, y))
			{
				emptyCells.push_back(make_pair(x, y));
			}
		}

	//소환할 곳이 없음
	if (emptyCells.empty())
		return;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, emptyCells.size() - 1);

	int randomIndex = distrib(gen);
	int randomX = emptyCells[randomIndex].first;
	int randomY = emptyCells[randomIndex].second;

	gameMap[randomY][randomX]->SetCellType(CellType::Prey);

	prevPreyPos = preyPos;
	preyPos.x = randomX;
	preyPos.y = randomY;
}

Point& GameMap::GetPreyPoint()
{
	return preyPos;
}

Point& GameMap::GetPrevPreyPoint()
{
	return prevPreyPos;
}

void GameMap::SpawnX2()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rand(0, 100);
	bool isSpawn = rand(gen) <= 10; //10%

	if (isSpawn)
	{
		vector<pair<int, int>> emptyCells;

		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				if (IsEmptyCell(x, y))
				{
					emptyCells.push_back(make_pair(x, y));
				}
			}

		//소환할 곳이 없음
		if (emptyCells.empty())
			return;

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> distrib(0, emptyCells.size() - 1 );

		int randomIndex = distrib(gen);
		int randomX = emptyCells[randomIndex].first;
		int randomY = emptyCells[randomIndex].second;

		gameMap[randomY][randomX]->SetCellType(CellType::X2);
	}
}

inline bool GameMap::IsEmptyCell(int x, int y)
{
	return gameMap[y][x]->GetCellType() == CellType::Empty;
}
