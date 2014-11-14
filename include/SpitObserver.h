#pragma once

#include "Vector.h"

class SpitObserver
{
public: 
	virtual void SpitEvent(Vector2 position_, float rotation_, float activeTime_) = 0; 
};