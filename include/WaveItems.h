#pragma once

#include <vector>
#include "Monster.h"
#include "PowerUp.h"

using namespace std;

struct WaveItems
{
	vector<Monster> monsterList;
	vector<PowerUp> powerUpList;
};

