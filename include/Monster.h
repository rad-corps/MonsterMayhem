#pragma once

#include "GameObject.h"

class Monster : public GameObject
{
public : 
	//pure virtuals
	virtual void Update(float delta_) = 0;
	virtual void Draw() = 0;
	virtual void HandleTerrainCollision() = 0;


	Monster();
	virtual ~Monster();

	void RegisterTarget(GameObject* target_);
	virtual void Hit(int power_ = 10.0f);

protected:
	int health;
	GameObject* target;
	Vector2 direction;
	bool CanSeePlayer();
};