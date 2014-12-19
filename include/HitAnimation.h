#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Enums.h"

class HitAnimation :
	public GameObject
{
public:
	HitAnimation(Vector2 pos_);
	~HitAnimation(void);

	virtual void Draw();
	virtual void Update(float delta_);

private:
	HIT_ANIMATION animation;
	float animationTimer;
	static unsigned int sprite;
};

