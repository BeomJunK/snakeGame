#pragma once

enum class GameState
{
	Ready,
	Play,
	End,
};

enum class CellType
{
	Empty,
	Wall,
	Prey,
	X2,
	Snake,
};

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
	ENTER = VK_RETURN,
};
enum class KEY_STATE
{
	NONE,
	PRESSED,
};
enum class Direction
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	END,
};

enum class Color : unsigned short
{
	Green = 10U,
	Red = 12U,
	WHITE = 15U,
};
