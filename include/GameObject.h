#pragma once

#include "Vector.h"

class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual void Update(float delta_) = 0;
	virtual void Draw() = 0;

	bool IsActive();

protected:
	Vector2 pos;
	int width;
	int height;
	bool active;
};

