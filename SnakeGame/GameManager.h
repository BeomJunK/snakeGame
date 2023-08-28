#pragma once
#include "GamePch.h"

class GameManager
{
	GameManager() {}
	~GameManager() {}
	GameManager& operator = (const GameManager& ref) {}

	GameState gameState = {};
	int score = {};
	int spawnRate = 1;

	//¸ÔÀÌ´ç Á¡¼ö
	const int preyScore = 10;
public:
	static GameManager& getInstance()
	{
		static GameManager mgr;
		return mgr;
	}

	void Inialize()
	{
		spawnRate = 0;
		score = 0;
	}

	GameState GetCurrentGameState()
	{
		return gameState;
	}
	void SetCurrentGameState(GameState state)
	{
		gameState = state;
	}
	int GetCurrentGameScore()
	{
		return score;
	}
	void AddCurrentGameScore(int score)
	{
		this->score += score;
	}
	void ResetGameScore()
	{
		this->score = 0;
	}
	void Reset()
	{
		this->score = 0;
		spawnRate = 1;
		gMap->Reset();
	}
	int GetCurrentPreySpawnRate()
	{
		return spawnRate;
	}
	void MultiflySpawnRate(int rate)
	{
		this->spawnRate *= rate;
	}
	void ResetSpawnRate()
	{
		this->spawnRate = 1;
	}

	inline int GetPrevScore()
	{
		return preyScore;
	}

};

