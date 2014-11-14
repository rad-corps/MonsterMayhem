#pragma once

#include "GameObject.h"

class Monster :
	public GameObject
{
public:
	Monster(void);
	~Monster(void);

	void RegisterTarget(GameObject* target_);
	void Hit(float power_ = 1.0f);
	virtual void Update(float delta_);
	virtual void Draw();

private:
	GameObject* target;
	Vector2 velocity;
	unsigned int sprite;
};

