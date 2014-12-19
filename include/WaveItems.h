#pragma once

#include <vector>
#include "MonsterSlug.h"
#include "PowerUp.h"
#include <memory>

using namespace std;

struct WaveItems
{
	vector<Monster*> monsterList;
	vector<PowerUp> powerUpList;

	int slugCount;
	int mothCount;
	int walkerCount;
};

