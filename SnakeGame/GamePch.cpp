#include "GamePch.h"
#include "GameMap.h"
#include "Input.h"

unique_ptr<GameMap> gMap = make_unique<GameMap>(50, 30, 1);
unique_ptr<Input> gInput = make_unique<Input>();
