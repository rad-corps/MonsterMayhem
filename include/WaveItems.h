//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// WaveItems.h
/////////////////////////////////////////////////////////////////////////

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

