#pragma once

#include "WaveItems.h"
#include "Player.h"

class WaveGen
{
public: 
	~WaveGen(void);

	static WaveItems Generate(int waveNum_, Player* player_);

private:
	WaveGen(void);

	static Vector2 RandomiseSafePosition(Vector2 target_, float safetyDistance_);
	static Monster SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_);
	
};

