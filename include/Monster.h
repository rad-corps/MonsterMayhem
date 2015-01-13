//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Monster.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "ExplosionObserver.h"
#include "Enums.h"

class Monster : public GameObject
{
public : 
	//pure virtuals
	virtual void Update(float delta_) = 0;
	virtual void Draw() = 0;
	virtual void HandleTerrainCollision() = 0;	
	virtual MONSTER_TYPE Type() = 0;

	void Rotate(); //rotate a fixed amount

	void SetInMud(bool inMud_);


	Monster();
	virtual ~Monster();

	void RegisterTarget(GameObject* target_);
	static void RegisterExplosionObserver(ExplosionObserver* explosionObserver_);
	virtual void Hit(int power_ = 10.0f);

protected:
	int health;
	int score;
	bool inMud;
	GameObject* target;
	Vector2 direction;
	bool CanSeePlayer();


private:
	static ExplosionObserver* explosionObserver;
	
};