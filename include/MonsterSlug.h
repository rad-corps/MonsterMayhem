//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterSlug.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Monster.h"
#include "Enums.h"
#include "Vector.h"
#include <queue>
#include "Node.h"
#include "PathFinder.h"

using namespace std;

class MonsterSlug :
	public Monster
{
public:
	MonsterSlug(Vector2 pos_);
	~MonsterSlug(void);

	//virtuals overridden
	virtual void Update(float delta_);
	virtual void Draw();
	virtual void HandleTerrainCollision();

	void Hit(int power = 10);

private:
	void SwitchMovementAnimation();
	void ResetMovementDirection();
	void UndoUpdate();
	//void GetNextNode();
	Vector2 RandomiseDirection();
	void RandomiseMovementTime();
	void RandomisePauseTime();

	Vector2 velocity;
	Vector2 previousPos;
	static unsigned int sprite;
	float speed;
	float movementTimer;
	float pauseTimer;
	float movementTimeLimit;
	float pauseTimeLimit;

	float timeSinceHit;
	

	MONSTER_STATE state;
	SLUG_ANIMATION animation;
	float animationTimer;

	queue<Node> path;
	Node currentDest;	
};

