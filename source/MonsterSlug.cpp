#include "MonsterSlug.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

using namespace std;

unsigned int MonsterSlug::sprite = 0;

float subtractSmallerNumber(float num1_, float num2_)
{
	if ( num1_ < num2_ )
		return num2_ - num1_;
	return num1_ - num2_;
}

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
	health = 10;
	speed = 100.f;
	if ( sprite == 0 )
	{
		sprite = CreateSprite("./images/Monster_Slug.png", width, height, true);
	}
	active = true;
	movementTimer = 0.0f;
	pauseTimer = 0.0f;
	//ResetMovementDirection();
	RandomisePauseTime();
	state = MONSTER_STATE::PAUSED;
}


MonsterSlug::~MonsterSlug(void)
{
	
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
}

void MonsterSlug::UndoUpdate()
{
	pos = previousPos;
}

bool MonsterSlug::CanSeePlayer()
{
	//are we within the enemy seeing distance? 
	float distanceToPlayer = (target->Pos() - pos).GetMagnitude();		
	if ( distanceToPlayer > FileSettings::GetFloat("SWARM_PLAYER_DISTANCE") )
		return false;

	//is the player within our cone? 
	Vector2 directionToPlayer = (target->Pos() - pos).GetNormal();
	Vector2 enemyFacing = direction.GetNormal();
	float difference = enemyFacing.AngleBetweenVectors(directionToPlayer);
	if ( difference > FileSettings::GetFloat("ENEMY_VIEW_FRUSTRUM") ) 
		return false;

	return true;
}

void MonsterSlug::Update(float delta_)
{
	if ( !active ) 
		return;

	previousPos = pos;

	if ( state == MONSTER_STATE::PAUSED )
	{
		pauseTimer += delta_;
		if ( pauseTimer >= pauseTimeLimit )
		{
			pauseTimer = 0.0f;
			ResetMovementDirection();			
		}
		return;
	}
	if ( state == MONSTER_STATE::MOVING )
	{
		//get distance to player
		float distanceToPlayer = (target->Pos() - pos).GetMagnitude();
		
		//if within SWARM_PLAYER_DISTANCE then swarm
		if ( CanSeePlayer() )
		{
			//move towards target
			direction = target->Pos() - pos;
			direction.Normalise();
			float deltaSpeed = (speed * 1.5f) * delta_;
			direction.SetMagnitude(deltaSpeed); //monster speed
			pos += direction;
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
		MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		DrawSprite(sprite);
	}
}