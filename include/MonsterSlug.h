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

	bool CanSeePlayer();

private:
	void ResetMovementDirection();
	void UndoUpdate();
	//void GetNextNode();
	Vector2 RandomiseDirection();
	void RandomiseMovementTime();
	void RandomisePauseTime();

	Vector2 velocity;
	Vector2 direction;
	Vector2 previousPos;
	static unsigned int sprite;
	float speed;
	float movementTimer;
	float pauseTimer;
	float movementTimeLimit;
	float pauseTimeLimit;
	

	MONSTER_STATE state;
	MONSTER_TYPE type;
//	PathFinder pf;

	queue<Node> path;
	Node currentDest;	
};

