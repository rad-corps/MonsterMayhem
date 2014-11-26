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

private:
	void GetNextNode();

	GameObject* target;
	Vector2 velocity;
	unsigned int sprite;
	float speed;
	int health;

//	PathFinder pf;

	queue<Node> path;
	Node currentDest;	
};

