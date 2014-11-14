#include "Spit.h"
#include "AIE.h"
#include "Enums.h"

Spit::Spit(void)
{
	sprite = CreateSprite("./images/Spit_Large.png", LOOGIE_W, LOOGIE_H, true);
	active = false;
}


Spit::~Spit(void)
{
}

void Spit::Update(float delta_)
{
	if ( activeCounter > activeTime )
	{
		active = false;
		return;
	}

	activeCounter += delta_;
	pos += velocity;
	MoveSprite(sprite, pos.x, pos.y);
}

void Spit::Draw()
{	
	if ( active ) 
		DrawSprite(sprite);
}

void Spit::HockOne(Vector2 position_, float rotation_, float activeTime_)
{
	active = true;
	pos = position_;
	velocity.SetAngle(rotation_);
	velocity.SetMagnitude(LOOGIE_VELOCITY);	
	activeTime = activeTime_;
	activeCounter = 0.0f;
}