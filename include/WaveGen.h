//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// WaveGen.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "WaveItems.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Rect.h"

using namespace std;

class WaveGen
{
public: 
	~WaveGen();

	static WaveItems Generate(int waveNum_, Player* player_, vector<Rect> unwalkableTerrain_);

private:
	WaveGen(void);

	static Vector2 RandomiseSafePosition(Vector2 target_, float safetyDistance_);
	static Monster* SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_);
	static vector<Rect> unwalkableTerrain;
	
};

