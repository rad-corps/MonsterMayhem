//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PowerUp.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "AIE.h"
#include "Enums.h"
#include "Vector.h"

class PowerUp : public GameObject
{
public:
	PowerUp();
	~PowerUp(void);

	virtual void Update(float delta_);
	virtual void Draw();
	POWER_UP_TYPE Eat();	


	void Spawn(POWER_UP_TYPE type_, Vector2 pos_);
	
	//randomise the power up type
	void Spawn(Vector2 pos_);

private:
	POWER_UP_TYPE type;
	bool anim;
	float animationTimer;
	unsigned int sprite;
	static unsigned int spriteSpeedup1;
	static unsigned int spriteSpeedup2;
	static unsigned int spritePowerUp1;
	static unsigned int spritePowerUp2;
	float timeSinceSpawn;
};

