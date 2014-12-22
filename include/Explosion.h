//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Explosion.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Enums.h"

class Explosion :
	public GameObject
{
public:
	Explosion(Vector2 pos_, Vector2 direction_);
	~Explosion(void);

	virtual void Draw();
	virtual void Update(float delta_);

private:
	EXPLOSION_ANIMATION animation;
	float animationTimer;
	static unsigned int sprite;
	Vector2 direction;
};

