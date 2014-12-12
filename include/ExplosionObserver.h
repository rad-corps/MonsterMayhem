#pragma once

#include "Vector.h"

class ExplosionObserver
{
public: 
	virtual void ExplosionEvent(Vector2 position_) = 0; 
};