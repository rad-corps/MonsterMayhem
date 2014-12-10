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

private:

	void RandomiseInitialDirection();
	void RandomiseNewDirection();

	static unsigned int sprite;	
	Vector2 velocity;

	float distTravelledSinceDirectionCalc;


	queue<Node> path;
	Node currentDest;	
};

