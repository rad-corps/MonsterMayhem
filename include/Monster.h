#pragma once

#include "GameObject.h"
#include "Enums.h"
#include "Vector.h"

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
	GameObject* target;
	Vector2 velocity;
	unsigned int sprite;
	int health;
};

