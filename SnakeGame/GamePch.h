#pragma once
#include <Windows.h>
#include <memory>
#include <iostream>
#include <format>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <functional>
#include <random>
#include <algorithm>
#include <string>
#include <ctime>

#include "GameMap.h"
#include "GameEnum.h"
#include "Input.h"
#include "Point.h"
#include "Cell.h"

using namespace std;

extern unique_ptr<GameMap> gMap;
extern unique_ptr<Input> gInput;
