#pragma once

#include "GameObject.h"
#include "Enums.h"
#include "Vector.h"
#include <queue>
#include "Node.h"
#include "PathFinder.h"

using namespace std;

class Monster :
	public GameObject
{
public:
	Monster(MONSTER_TYPE type_, Vector2 pos_);
	~Monster(void);

	void RegisterTarget(GameObject* target_);
	void Hit(int power_ = 10.0f);
	virtual void Update(float delta_);
	virtual void Draw();
	void ResetMovementDirection();
	void UndoUpdate();

private:
	//void GetNextNode();
	Vector2 RandomiseDirection();
	void RandomiseMovementTime();
	void RandomisePauseTime();
	

	GameObject* target;
	Vector2 velocity;
	Vector2 direction;
	Vector2 previousPos;
	unsigned int sprite;
	float speed;
	float movementTimer;
	float pauseTimer;
	float movementTimeLimit;
	float pauseTimeLimit;
	int health;

	MONSTER_STATE state;

//	PathFinder pf;

	queue<Node> path;
	Node currentDest;	
};

