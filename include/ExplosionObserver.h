#pragma once

#include "Vector.h"

class ExplosionObserver
{
public: 
	virtual void ExplosionEvent(Vector2 position_, Vector2 direction_, int score_) = 0; 
};