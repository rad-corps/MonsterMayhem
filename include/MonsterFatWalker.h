//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterFatWalker.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Monster.h"
#include "Enums.h"
#include "Vector.h"
#include "Node.h"

class MonsterFatWalker :
	public Monster
{

public:
	MonsterFatWalker(Vector2 pos_);
	~MonsterFatWalker(void);

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
	
	FAT_WALKER_ANIMATION animation;
	float animationTimer;
	MONSTER_STATE state;
};