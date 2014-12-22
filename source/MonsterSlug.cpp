//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterSlug.cpp
/////////////////////////////////////////////////////////////////////////

#include "MonsterSlug.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

using namespace std;

unsigned int MonsterSlug::sprite = 0;

float SLUG_STATIONARY_UV[4] = { SLUG_U_MIN                      , SLUG_V_MIN  , SLUG_U_MIN +   SLUG_U_STEP    , SLUG_V_MIN + SLUG_V_STEP };
float SLUG_MOVEMENT1_UV[4] = { SLUG_U_MIN + SLUG_U_STEP        , SLUG_V_MIN  , SLUG_U_MIN +   SLUG_U_STEP * 2, SLUG_V_MIN + SLUG_V_STEP };                        
float SLUG_MOVEMENT2_UV[4] = { SLUG_U_MIN + SLUG_U_STEP     * 2, SLUG_V_MIN  , SLUG_U_MIN +   SLUG_U_STEP * 3, SLUG_V_MIN + SLUG_V_STEP };
float SLUG_HIT_UV[4] =       { SLUG_U_MIN + SLUG_U_STEP     * 3, SLUG_V_MIN  , SLUG_U_MIN +   SLUG_U_STEP * 4, SLUG_V_MIN + SLUG_V_STEP };

void MonsterSlug::HandleTerrainCollision()
{
	UndoUpdate();
	ResetMovementDirection();
}


MonsterSlug::MonsterSlug(Vector2 pos_)
{
	pos = pos_;
	//default width and height for enemies
	width = 64;
	height = 64;
	health = 20;
	speed = 100.f;
	score = 20;
	if ( sprite == 0 )
	{
		sprite = CreateSprite("./images/Character_sprite_sheet.png", width, height, true);
	}
	active = true;
	movementTimer = 0.0f;
	pauseTimer = 0.0f;
	//ResetMovementDirection();
	RandomisePauseTime();
	state = MONSTER_STATE::PAUSED;
	animation = SLUG_ANIMATION::SLUG_ANIM_STATIONARY;
	animationTimer = 0.0f;
	timeSinceHit = 100.f;
}


MonsterSlug::~MonsterSlug(void)
{
	
}

void MonsterSlug::Hit(int power_)
{
	Monster::Hit(power_);
	animation = SLUG_ANIMATION::SLUG_ANIM_HIT;
	animationTimer = 0.0f;
	timeSinceHit = 0.0f;
}

//return up, down, left or right
Vector2 MonsterSlug::RandomiseDirection()
{
	Vector2 ret; 
	int num = rand() % 4; //number between 0 and 3 inclusive	
	ret.SetAngle(num * (PI / 2));
	return ret;
}

void MonsterSlug::RandomisePauseTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("PAUSE_TIME_MAX") - FileSettings::GetFloat("PAUSE_TIME_MIN");
    float r = random * diff;
	pauseTimeLimit = FileSettings::GetFloat("PAUSE_TIME_MIN") + r;
}

void MonsterSlug::RandomiseMovementTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("MOVEMENT_TIMER_MAX") - FileSettings::GetFloat("MOVEMENT_TIMER_MIN");
    float r = random * diff;
    movementTimeLimit = FileSettings::GetFloat("MOVEMENT_TIMER_MIN") + r;
}

void MonsterSlug::ResetMovementDirection()
{
	direction = RandomiseDirection();
	RandomiseMovementTime();
	state = MONSTER_STATE::MOVING;	
	animation = SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1;
}

void MonsterSlug::UndoUpdate()
{
	pos = previousPos;
}

void MonsterSlug::SwitchMovementAnimation()
{
	animationTimer = 0.0f;

	if ( animation == SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1 ) 
		animation = SLUG_ANIMATION::SLUG_ANIM_MOVEMENT2;
	else if ( animation == SLUG_ANIMATION::SLUG_ANIM_MOVEMENT2 ) 
		animation = SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1;
	else if ( animation != SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1 && animation != SLUG_ANIMATION::SLUG_ANIM_MOVEMENT2 )
		animation = SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1;
}

void MonsterSlug::Update(float delta_)
{
	if ( !active ) 
		return;

	previousPos = pos;
	animationTimer += delta_;

	timeSinceHit += delta_;

	if ( timeSinceHit < 0.1f )
	{
		animation = SLUG_ANIMATION::SLUG_ANIM_HIT;
		return;
	}

	if ( state == MONSTER_STATE::PAUSED )
	{
		animation = SLUG_ANIMATION::SLUG_ANIM_STATIONARY;
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
		if (animationTimer > 0.1f )
		{
			SwitchMovementAnimation();
		}

		float deltaSpeed = (speed * 2.0f) * delta_;
		direction.SetMagnitude(deltaSpeed); //monster speed
		pos += direction;
		movementTimer += delta_;
		if ( movementTimer > movementTimeLimit )
		{
			RandomisePauseTime();
			state = MONSTER_STATE::PAUSED;
			animation = SLUG_ANIMATION::SLUG_ANIM_STATIONARY;
			animationTimer = 0.0f;
			movementTimer = 0.0f;
		}
	}
	if ( state == MONSTER_STATE::MOVING )
	{
		if (animationTimer > 0.2f )
		{
			SwitchMovementAnimation();
		}
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
			pos += velocity;
		}
	}
}



void MonsterSlug::Draw()
{
	if ( active ) 
	{
		if ( animation == SLUG_ANIMATION::SLUG_ANIM_STATIONARY)
			SetSpriteUVCoordinates	( sprite, SLUG_STATIONARY_UV);
		if ( animation == SLUG_ANIMATION::SLUG_ANIM_MOVEMENT1)
			SetSpriteUVCoordinates	( sprite, SLUG_MOVEMENT1_UV);
		if ( animation == SLUG_ANIMATION::SLUG_ANIM_MOVEMENT2)
			SetSpriteUVCoordinates	( sprite, SLUG_MOVEMENT2_UV);
		if ( animation == SLUG_ANIMATION::SLUG_ANIM_HIT)
			SetSpriteUVCoordinates	( sprite, SLUG_HIT_UV);

		MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		RotateSprite(sprite, 270.0f);
		DrawSprite(sprite);
	}
}