//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Spit.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "Vector.h"

class Spit : public GameObject
{
public:
	Spit(void);
	~Spit(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void HockOne(Vector2 position_, float rotation_, float activeTime_);

private:
	//float rotation;
	Vector2 velocity;
	float activeTime;
	float activeCounter;
	unsigned int sprite;
};

