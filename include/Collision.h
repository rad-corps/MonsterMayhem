#pragma once

#include "GameObject.h"

class Collision
{
public:
	~Collision(void);

	static bool CheckCollision(GameObject* obj1_, GameObject* obj2_);

private:
	Collision(void);
	
};

