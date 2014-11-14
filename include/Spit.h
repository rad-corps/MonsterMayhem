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

