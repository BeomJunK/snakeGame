#include "GamePch.h"

unique_ptr<GameMap> gMap = make_unique<GameMap>(30, 30, 1);
unique_ptr<Input> gInput = make_unique<Input>();
