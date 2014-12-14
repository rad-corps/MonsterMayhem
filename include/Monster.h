#pragma once

#include "GameObject.h"
#include "ExplosionObserver.h"

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
	static void RegisterExplosionObserver(ExplosionObserver* explosionObserver_);
	virtual void Hit(int power_ = 10.0f);

protected:
	int health;
	int score;
	GameObject* target;
	Vector2 direction;
	bool CanSeePlayer();


private:
	static ExplosionObserver* explosionObserver;
};