//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// SpitObserver.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"

class SpitObserver
{
public: 
	virtual void SpitEvent(Vector2 position_, float rotation_, float activeTime_) = 0; 
};