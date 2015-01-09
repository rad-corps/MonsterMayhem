//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterMoth.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Monster.h"
#include "Enums.h"
#include "Vector.h"
#include <queue>
#include "Node.h"
#include "PathFinder.h"

using namespace std;

class MonsterMoth :
	public Monster
{
public:
	MonsterMoth(Vector2 pos_);
	~MonsterMoth(void);

	//virtuals overridden
	virtual void Update(float delta_);
	virtual void Draw();
	virtual void HandleTerrainCollision();
	virtual MONSTER_TYPE Type(){return MONSTER_TYPE::MOTH;}

	void Hit(int power = 10);

private:

	void RandomiseInitialDirection();
	void RandomiseNewDirection();

	static unsigned int sprite;	
	Vector2 velocity;
	float animationTimer;
	MOTH_ANIMATION animation;

	float distTravelledSinceDirectionCalc;


	//queue<Node> path;
	//Node currentDest;	
};

