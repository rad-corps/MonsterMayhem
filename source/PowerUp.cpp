#include "PowerUp.h"
#include "AIE.h"
#include "FileSettings.h"

PowerUp::PowerUp(void)
{
	active = false;
	sprite = 0;
	width = POWER_UP_W;
	height = POWER_UP_H;
}


PowerUp::~PowerUp(void)
{
	timeSinceSpawn = 100000.0f;
}

void PowerUp::Update(float delta_)
{
	timeSinceSpawn += delta_;

	if (timeSinceSpawn > FileSettings::GetFloat("MAX_POWER_UP_TIME") ) 
	{
		active = false;
	}
	if ( sprite != 0 && active )
	{
		MoveSprite(sprite, pos.x, pos.y);
	}
}

void PowerUp::Draw()
{
	if ( sprite != 0 && active )
	{
		DrawSprite(sprite);
	}
}

void PowerUp::Spawn(POWER_UP_TYPE type_, Vector2 pos_)
{
	type = type_;
	if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
		sprite = CreateSprite("./images/Power_up_64.png", POWER_UP_W, POWER_UP_H, true);
	if ( type == POWER_UP_TYPE::SPEED_UP) 
		sprite = CreateSprite("./images/Speed_up_64.png", POWER_UP_W, POWER_UP_H, true);

	timeSinceSpawn = 0.0f;

	pos = pos_;

	active = true;
}

void PowerUp::Spawn(Vector2 pos_)
{
	int chance = rand() % 10 + 1;
	if ( chance < 5 ) 
		Spawn(POWER_UP_TYPE::SPEED_UP, pos_);
	else
		Spawn(POWER_UP_TYPE::SPIT_FREQUENCY, pos_);
}

POWER_UP_TYPE PowerUp::Eat()
{	
	active = false;
	
	//we can assume that sprite is set if we get to here. 
	DestroySprite(sprite);
	
	return type;
}