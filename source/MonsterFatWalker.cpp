//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterFatWalker.cpp
/////////////////////////////////////////////////////////////////////////

#include "MonsterFatWalker.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

using namespace std;

float WALKER_STATIONARY_UV[4] = { WALKER_U_MIN                    , WALKER_V_MIN  , WALKER_U_MIN +   WALKER_U_STEP    , WALKER_V_MIN + WALKER_V_STEP };
float WALKER_MOVEMENT1_UV[4]  = { WALKER_U_MIN + WALKER_U_STEP    , WALKER_V_MIN  , WALKER_U_MIN +   WALKER_U_STEP * 2, WALKER_V_MIN + WALKER_V_STEP };                        
float WALKER_MOVEMENT2_UV[4]  = { WALKER_U_MIN + WALKER_U_STEP * 2, WALKER_V_MIN  , WALKER_U_MIN +   WALKER_U_STEP * 3, WALKER_V_MIN + WALKER_V_STEP };
float WALKER_HIT_UV[4]        = { WALKER_U_MIN + WALKER_U_STEP * 3, WALKER_V_MIN  , WALKER_U_MIN +   WALKER_U_STEP * 4, WALKER_V_MIN + WALKER_V_STEP };

unsigned int MonsterFatWalker::sprite = 0;

void MonsterFatWalker::HandleTerrainCollision()
{
	UndoUpdate();
	//ResetMovementDirection();
	Rotate();
}


MonsterFatWalker::MonsterFatWalker(Vector2 pos_)
{
	pos = pos_;
	//default width and height for enemies
	width = 64;
	height = 64;
	health = 40;
	speed = 150.f;
	score = 50;
	if ( sprite == 0 )
	{
		sprite = CreateSprite("./images/Character_sprite_sheet.png", width, height, true);
	}
	active = true;
	movementTimer = 0.0f;
	pauseTimer = 0.0f;
	timeSinceHit = 100.f;
	//ResetMovementDirection();
	RandomisePauseTime();
	state = MONSTER_STATE::PAUSED;
	animation = FAT_WALKER_ANIMATION::WALKER_ANIM_STATIONARY;
	animationTimer = 0.0f;
	inMud = false;
}


MonsterFatWalker::~MonsterFatWalker(void)
{
	
}

//return up, down, left or right
Vector2 MonsterFatWalker::RandomiseDirection()
{
	Vector2 ret; 
	int num = rand() % 4; //number between 0 and 3 inclusive	
	ret.SetAngle(num * (PI / 2));
	return ret;
}

void MonsterFatWalker::RandomisePauseTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("PAUSE_TIME_MAX") - FileSettings::GetFloat("PAUSE_TIME_MIN");
    float r = random * diff;
	pauseTimeLimit = FileSettings::GetFloat("PAUSE_TIME_MIN") + r;
}

void MonsterFatWalker::RandomiseMovementTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("MOVEMENT_TIMER_MAX") - FileSettings::GetFloat("MOVEMENT_TIMER_MIN");
    float r = random * diff;
    movementTimeLimit = FileSettings::GetFloat("MOVEMENT_TIMER_MIN") + r;
}

void MonsterFatWalker::ResetMovementDirection()
{
	direction = RandomiseDirection();
	RandomiseMovementTime();
	state = MONSTER_STATE::MOVING;	
}

void MonsterFatWalker::UndoUpdate()
{
	pos = previousPos;
}

void MonsterFatWalker::SwitchMovementAnimation()
{
	animationTimer = 0.0f;
	if  (animation != FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT1 && animation != FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT2)
	{
		animation = FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT1;
		return;
	}
	if ( animation == FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT1 )
		animation = FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT2;
	else if ( animation == FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT2 )
		animation = FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT1;
}

void MonsterFatWalker::Update(float delta_)
{
	if ( !active ) 
		return;


	animationTimer += delta_;
	previousPos = pos;
	timeSinceHit += delta_;

	if ( timeSinceHit < 0.1f )
	{
		animation = FAT_WALKER_ANIMATION::WALKER_ANIM_HIT;
		return;
	}

	if ( state == MONSTER_STATE::PAUSED )
	{
		animation = FAT_WALKER_ANIMATION::WALKER_ANIM_STATIONARY;

		pauseTimer += delta_;
		if ( pauseTimer >= pauseTimeLimit )
		{
			pauseTimer = 0.0f;
			ResetMovementDirection();			
		}
		return;
	}
	if ( state == MONSTER_STATE::CHARGING )
	{
		if ( animationTimer > 0.15f ) 
			SwitchMovementAnimation();

		float deltaSpeed = (speed * 2.0f) * delta_;
		direction.SetMagnitude(deltaSpeed); //monster speed
		

		if  (inMud)
			pos += direction * 0.5f;
		else
			pos += direction;

		movementTimer += delta_;
		if ( movementTimer > movementTimeLimit )
		{
			RandomisePauseTime();
			state = MONSTER_STATE::PAUSED;
			movementTimer = 0.0f;
		}
	}
	if ( state == MONSTER_STATE::MOVING )
	{
		if ( animationTimer > 0.3f ) 
			SwitchMovementAnimation();

		//get distance to player
		float distanceToPlayer = (target->Pos() - pos).GetMagnitude();
		
		//if within SWARM_PLAYER_DISTANCE then swarm
		if ( CanSeePlayer() )
		{
			//move towards target
			direction = target->Pos() - pos;
			direction.Normalise();
			state = MONSTER_STATE::CHARGING;
			movementTimer = 0.0f;
		}

		else //else walk around like a peanut
		{
			movementTimer += delta_;

			if ( movementTimer > movementTimeLimit )
			{
				RandomisePauseTime();
				state = MONSTER_STATE::PAUSED;
				movementTimer = 0.0f;
			}
		
			float deltaSpeed = speed * delta_;
			velocity = direction;
			velocity.SetMagnitude(deltaSpeed);
			
			if ( inMud ) 
				pos += velocity * 0.5f;
			else
				pos += velocity;
		}
	}
}



void MonsterFatWalker::Draw()
{
	if ( active ) 
	{
		//get animation to use
		switch (animation)
		{
		case FAT_WALKER_ANIMATION::WALKER_ANIM_STATIONARY : 
			SetSpriteUVCoordinates	( sprite, WALKER_STATIONARY_UV);
			break;
		case FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT1 : 
			SetSpriteUVCoordinates	( sprite, WALKER_MOVEMENT1_UV);
			break;
		case FAT_WALKER_ANIMATION::WALKER_ANIM_MOVEMENT2 : 
			SetSpriteUVCoordinates	( sprite, WALKER_MOVEMENT2_UV);
			break;
		case FAT_WALKER_ANIMATION::WALKER_ANIM_HIT: 
			SetSpriteUVCoordinates	( sprite, WALKER_HIT_UV);
			break;
		}


		
		RotateSpriteToVector(sprite, direction);
		RotateSprite(sprite, 270.0f);
		//DrawSprite(sprite);
		//MoveSprite(sprite, pos.x, pos.y);
		DrawIfOnScreen(sprite, pos.x, pos.y);
	}
}

void MonsterFatWalker::Hit(int power_)
{
	Monster::Hit(power_);
	timeSinceHit = 0.0f;
}