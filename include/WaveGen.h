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
	
};

