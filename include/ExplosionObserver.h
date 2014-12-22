//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// ExplosionObserver.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"

class ExplosionObserver
{
public: 
	virtual void ExplosionEvent(Vector2 position_, Vector2 direction_, int score_) = 0; 
};