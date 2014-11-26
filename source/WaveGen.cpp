#include "WaveGen.h"


WaveGen::WaveGen(void)
{
}


WaveGen::~WaveGen(void)
{
}


//we dont want to spawn enemies to close to the player or ontop of the player. 
//keep it fair ;)
Vector2 WaveGen::RandomiseSafePosition(Vector2 target_, float safetyDistance_)
{
	//randomise a position
	int xPos = rand() % (BATTLE_FIELD_W - TERRAIN_W * 4) + (TERRAIN_W * 2);
	int yPos = rand() % (BATTLE_FIELD_H - TERRAIN_H * 4) + (TERRAIN_H * 2);
	Vector2 pos = Vector2(xPos,yPos);

	//check pos against the target_ pos
	float distance = (target_ - pos).GetMagnitude();
	if ( distance < safetyDistance_ ) 
		return RandomiseSafePosition(target_, safetyDistance_); //try again
	return pos;
}

Monster WaveGen::SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_)
{
	Vector2 pos = RandomiseSafePosition(player_->Pos(), safetyDistance_);
	Monster temp(type_, pos);
	temp.RegisterTarget(player_);
	return temp;
}

//Monster WaveGen::SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_)
//{
//	cout << "test implementation of WaveGen::SpawnMonster" << endl;
//	Vector2 pos(1,1);
//	Monster temp(type_, pos);
//	temp.RegisterTarget(player_);
//	return temp;
//}

//WaveItems WaveGen::Generate(int waveNum_, Player* player_)
//{
//	cout << "test implementation of WaveGen::Generate" << endl;
//	WaveItems ret;
//	vector<Monster> monsterList;
//	monsterList.push_back(SpawnMonster(MONSTER_TYPE::MEDIUM, player_, SAFE_SPAWN_DISTANCE));
//	ret.monsterList = monsterList;	
//	return ret;
//}

WaveItems WaveGen::Generate(int waveNum_, Player* player_)
{
	cout << "Generating Wave " << waveNum_ << endl;
	
	//set up the return value
	WaveItems ret;
	vector<Monster> monsterList;
	vector<PowerUp> powerUpList;
	

	//create some random monsters
	for (int i = 0; i < 20; ++i )
	{
		monsterList.push_back(SpawnMonster(MONSTER_TYPE::MEDIUM, player_, SAFE_SPAWN_DISTANCE));
	}

	if ( waveNum_ >= 3 ) 
	{
		for (int i = 0; i < 5*(waveNum_%3+1); ++i )
		{
			monsterList.push_back(SpawnMonster(MONSTER_TYPE::LARGE, player_, SAFE_SPAWN_DISTANCE));
		}
	}

	if ( waveNum_ >= 5 ) 
	{
		for (int i = 0; i < 2*(waveNum_%3+4); ++i )
		{
			monsterList.push_back(SpawnMonster(MONSTER_TYPE::BOSS, player_, SAFE_SPAWN_DISTANCE));
		}
	}

	//create some power ups
	for ( int i = 0; i < 3 + waveNum_ * 0.2f; ++i )
	{
		PowerUp temp;
		temp.Spawn(POWER_UP_TYPE::SPEED_UP);
		powerUpList.push_back(temp);		
	}
	
	for ( int i = 0; i < 3 + waveNum_ * 0.2f; ++i )
	{
		PowerUp temp;
		temp.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY);
		powerUpList.push_back(temp);		
	}

	ret.monsterList = monsterList;
	ret.powerUpList = powerUpList;
	
	return ret;
}