#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Enums.h"

class Explosion :
	public GameObject
{
public:
	Explosion(Vector2 pos_);
	~Explosion(void);

	virtual void Draw();
	virtual void Update(float delta_);

private:
	EXPLOSION_ANIMATION animation;
	float animationTimer;
	static unsigned int sprite;
};

