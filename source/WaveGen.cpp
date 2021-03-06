//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// WaveGen.cpp
/////////////////////////////////////////////////////////////////////////

#include "WaveGen.h"
#include "Collision.h"
#include "MonsterMoth.h"
#include "MonsterSlug.h"
#include "MonsterFatWalker.h"
#include "FileSettings.h"


vector<Rect> WaveGen::unwalkableTerrain;

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
	int xPos = rand() % (FileSettings::GetInt("BATTLE_FIELD_W") - TERRAIN_W * 4) + (TERRAIN_W * 2);
	int yPos = rand() % (FileSettings::GetInt("BATTLE_FIELD_H") - TERRAIN_H * 4) + (TERRAIN_H * 2);
	Vector2 pos = Vector2(xPos,yPos);

	//check pos against the target_ pos
	float distance = (target_ - pos).GetMagnitude();
	if ( distance < safetyDistance_ ) 
		return RandomiseSafePosition(target_, safetyDistance_); //try again


	//Check pos against the unwalkable terrain
	Rect newPos(Vector2(xPos, yPos), 64, 64);
	for ( int i = 0; i < unwalkableTerrain.size(); ++i )
	{
		if ( Collision::RectCollision(newPos, unwalkableTerrain[i]))
		{
			return RandomiseSafePosition(target_, safetyDistance_); //try again
		}
	}	
	return pos;
}

Monster* WaveGen::SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_)
{
	Vector2 pos = RandomiseSafePosition(player_->Pos(), safetyDistance_);
	Monster* ret;
	if ( type_ == MONSTER_TYPE::SLUG )
		ret = new MonsterSlug(pos);
	if ( type_ == MONSTER_TYPE::MOTH )
		ret = new MonsterMoth(pos);
	if ( type_ == MONSTER_TYPE::FAT_WALKER )
		ret = new MonsterFatWalker(pos);
	
	ret->RegisterTarget(player_);
	return ret;
}

//Monster WaveGen::SpawnMonster(MONSTER_TYPE type_, Player* player_, float safetyDistance_)
//{
//	cout << "test implementation of WaveGen::SpawnMonster" << endl;
//	Vector2 pos(1,1);
//	Monster temp(type_, pos);
//	temp.RegisterTarget(player_);
//	return temp;
//}

//test Generate function that spawns only one enemy
//WaveItems WaveGen::Generate(int waveNum_, Player* player_)
//{
//	cout << "test implementation of WaveGen::Generate" << endl;
//	WaveItems ret;
//	vector<Monster> monsterList;
//	monsterList.push_back(SpawnMonster(MONSTER_TYPE::MEDIUM, player_, SAFE_SPAWN_DISTANCE));
//	ret.monsterList = monsterList;	
//	return ret;
//}

WaveItems WaveGen::Generate(int waveNum_, Player* player_, vector<Rect> unwalkableTerrain_)
{
	cout << "Generating Wave " << waveNum_ << endl;

	unwalkableTerrain = unwalkableTerrain_;

	//set up the return value
	WaveItems ret;
	vector<Monster*> monsterList;
	vector<PowerUp> powerUpList;
	

	//create some random monsters
	//const int MAX_NUM_OF_SLUGS = waveNum_ * 4.f;
	const int MAX_NUM_OF_SLUGS = FileSettings::GetInt("SLUGS");
	//int numOfSlugs = rand() % MAX_NUM_OF_SLUGS + 1;
	//cout << "numOfSlugs : " << numOfSlugs << endl;
	ret.slugCount = MAX_NUM_OF_SLUGS;
	for (int i = 0; i < MAX_NUM_OF_SLUGS; ++i )
	{
		monsterList.push_back(SpawnMonster(MONSTER_TYPE::SLUG, player_, SAFE_SPAWN_DISTANCE));
	}

	//const int MAX_NUM_OF_MOTHS = waveNum_ * 2.3f;
	const int MAX_NUM_OF_MOTHS = FileSettings::GetInt("MOTHS");;
	//int numOfMoths = rand() % MAX_NUM_OF_MOTHS + 1;
	//cout << "numOfMoths : " << numOfMoths << endl;
	ret.mothCount = MAX_NUM_OF_MOTHS;
	for (int i = 0; i < MAX_NUM_OF_MOTHS; ++i )
	{
		monsterList.push_back(SpawnMonster(MONSTER_TYPE::MOTH, player_, SAFE_SPAWN_DISTANCE));
	}
	
	//const int MAX_NUM_OF_WALKERS = waveNum_ * 1.0f;
	const int MAX_NUM_OF_WALKERS = FileSettings::GetInt("WALKERS");;
	//int numOfFatWalkers = rand() % MAX_NUM_OF_WALKERS + 1;
	//cout << "numOfFatWalkers : " << numOfFatWalkers << endl;
	ret.walkerCount = MAX_NUM_OF_WALKERS;
	for (int i = 0; i < MAX_NUM_OF_WALKERS; ++i )
	{
		monsterList.push_back(SpawnMonster(MONSTER_TYPE::FAT_WALKER, player_, SAFE_SPAWN_DISTANCE));
	}
	

	////create some power ups
	//for ( int i = 0; i < 3 + waveNum_ * 0.2f; ++i )
	//{
	//	PowerUp temp;
	//	temp.Spawn(POWER_UP_TYPE::SPEED_UP, RandomiseSafePosition(player_->Pos(), 100.f));
	//	powerUpList.push_back(temp);		
	//}
	//
	//for ( int i = 0; i < 3 + waveNum_ * 0.2f; ++i )
	//{
	//	PowerUp temp;
	//	temp.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY, RandomiseSafePosition(player_->Pos(), 100.f));
	//	powerUpList.push_back(temp);		
	//}

	ret.monsterList = monsterList;
	ret.powerUpList = powerUpList;
	
	return ret;
}