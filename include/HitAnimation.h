//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// HitAnimation.h
/////////////////////////////////////////////////////////////////////////

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

