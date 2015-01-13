//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PowerUp.cpp
/////////////////////////////////////////////////////////////////////////

#include "PowerUp.h"
#include "AIE.h"
#include "FileSettings.h"
#include "Sound.h"

//initialise statics
unsigned int PowerUp::spriteSpeedup1 = 0;
unsigned int PowerUp::spriteSpeedup2 = 0;
unsigned int PowerUp::spritePowerUp1 = 0;
unsigned int PowerUp::spritePowerUp2 = 0;

PowerUp::PowerUp(void)
{
	anim = false;
	//create sprites if they have not been created
	if ( spriteSpeedup1 == 0 )
	{
		spriteSpeedup1 = CreateSprite("./images/speed_up_1.png", POWER_UP_W, POWER_UP_H, true);
		spriteSpeedup2 = CreateSprite("./images/speed_up_2.png", POWER_UP_W, POWER_UP_H, true);
		spritePowerUp1 = CreateSprite("./images/power_up_1.png", POWER_UP_W, POWER_UP_H, true);
		spritePowerUp2 = CreateSprite("./images/power_up_2.png", POWER_UP_W, POWER_UP_H, true);
	}

	active = false;
//	sprite = 0;
	width = POWER_UP_W;
	height = POWER_UP_H;
	animationTimer = 0.0f;
}


PowerUp::~PowerUp(void)
{
	//arbitrary high value because we do not spawn on object creation. 
	timeSinceSpawn = 100000.0f;
}

void PowerUp::Update(float delta_)
{
	timeSinceSpawn += delta_;
	animationTimer += delta_;

	//swap animation
	if ( timeSinceSpawn < FileSettings::GetFloat("MAX_POWER_UP_TIME") / 2 )
	{
		if ( animationTimer > 0.2f )
		{
			animationTimer = 0.0f;
			anim = !anim;
		}
	}
	else
	{
		if ( animationTimer > 0.1f )
		{
			animationTimer = 0.0f;
			anim = !anim;
		}
	}
	
	if (timeSinceSpawn > FileSettings::GetFloat("MAX_POWER_UP_TIME") ) 
	{
		active = false;
	}
}

void PowerUp::Draw()
{
	//if ( sprite != 0 && active )
	if ( active )
	{
		if ( type == POWER_UP_TYPE::SPEED_UP  && anim) 
		{
			sprite = spriteSpeedup1;
		}
		else if (  type == POWER_UP_TYPE::SPEED_UP  && !anim) 
		{
			sprite = spriteSpeedup2;
		}
		else if (  type == POWER_UP_TYPE::SPIT_FREQUENCY && anim) 
		{
			sprite = spritePowerUp1;
		}
		else if (  type == POWER_UP_TYPE::SPIT_FREQUENCY && !anim) 
		{
			sprite = spritePowerUp2;
		}

		MoveSprite(sprite, pos.x, pos.y);
		DrawSprite(sprite);		
	}
}

void PowerUp::Spawn(POWER_UP_TYPE type_, Vector2 pos_)
{
	type = type_;
	//if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
	//	sprite = CreateSprite("./images/power_up_1.png", POWER_UP_W, POWER_UP_H, true);
	//if ( type == POWER_UP_TYPE::SPEED_UP) 
	//	sprite = CreateSprite("./images/speed_up_1.png", POWER_UP_W, POWER_UP_H, true);

	timeSinceSpawn = 0.0f;

	pos = pos_;

	active = true;
	animationTimer = 0.0f;	
	
}

void PowerUp::Spawn(Vector2 pos_)
{
	cout << "Spawn(" << pos_ << ");" << endl;
	
	Sound::PlayGameSound(SOUNDS::PICKUP_DROP);

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
	//DestroySprite(sprite);
	
	return type;
}