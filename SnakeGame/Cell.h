#pragma once
#include "GamePch.h"
#include "GameEnum.h"

class Cell
{
public:
	Cell();

	void SetCellType(CellType type) { this->type = type; }
	CellType GetCellType() { return type; }
private:
	CellType type;
};

