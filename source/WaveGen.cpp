#include "WaveGen.h"


WaveGen::WaveGen(void)
{
}


WaveGen::~WaveGen(void)
{
}


WaveItems WaveGen::Generate(int waveNum_, Player* player_)
{
	cout << "Generating Wave " << waveNum_ << endl;
	
	//set up the return value
	WaveItems ret;
	vector<Monster> monsterList;
	vector<PowerUp> powerUpList;
	

	//create some random monsters
	for (int i = 0; i < 20*waveNum_; ++i )
	{
		Monster temp;
		temp.RegisterTarget(player_);
		monsterList.push_back(temp);
	}

	//create some power ups
	for ( int i = 0; i < 1*waveNum_; ++i )
	{
		PowerUp temp;
		temp.Spawn(POWER_UP_TYPE::SPEED_UP);
		powerUpList.push_back(temp);		
	}
	
	for ( int i = 0; i < 1*waveNum_; ++i )
	{
		PowerUp temp;
		temp.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY);
		powerUpList.push_back(temp);		
	}

	ret.monsterList = monsterList;
	ret.powerUpList = powerUpList;
	
	return ret;
}