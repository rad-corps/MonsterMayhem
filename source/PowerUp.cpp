#include "PowerUp.h"
#include "AIE.h"

PowerUp::PowerUp(void)
{
	active = false;
	sprite = 0;
	width = POWER_UP_W;
	height = POWER_UP_H;
}


PowerUp::~PowerUp(void)
{
}

void PowerUp::Update(float delta_)
{
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

void PowerUp::Spawn(POWER_UP_TYPE type_)
{
	type = type_;
	if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
		sprite = CreateSprite("./images/Power_up_64.png", POWER_UP_W, POWER_UP_H, true);
	if ( type == POWER_UP_TYPE::SPEED_UP) 
		sprite = CreateSprite("./images/Speed_up_64.png", POWER_UP_W, POWER_UP_H, true);

	//randomise location
	int xPos = rand() % BATTLE_FIELD_W;
	int yPos = rand() % BATTLE_FIELD_H;

	pos.x = xPos;
	pos.y = yPos;

	active = true;
}

POWER_UP_TYPE PowerUp::Eat()
{	
	active = false;
	return type;
}