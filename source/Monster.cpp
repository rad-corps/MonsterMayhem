#include "Monster.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

using namespace std;




Monster::Monster(MONSTER_TYPE type_, Vector2 pos_)
{
	pos = pos_;
	switch (type_)
	{
		case MONSTER_TYPE::MEDIUM :
			width = 32;
			height = 32;
			health = 10;
			speed = 100.f;
			sprite = CreateSprite("./images/Monster_Medium.png", width, height, true);
			break;
		case MONSTER_TYPE::LARGE : 
			width = 64;
			height = 64;
			health = 20;
			speed = 133.f;
			sprite = CreateSprite("./images/Monster_Large.png", width, height, true);
			break;
		case MONSTER_TYPE::BOSS: 
			width = 128;
			height = 128;
			health = 40;
			speed = 200.f;
			sprite = CreateSprite("./images/Monster_Boss.png", width, height, true);
			break;
	}
	active = true;
	movementTimer = 0.0f;
	pauseTimer = 0.0f;
	//ResetMovementDirection();
	RandomisePauseTime();
	state = MONSTER_STATE::PAUSED;
}


Monster::~Monster(void)
{
	
}

void Monster::RegisterTarget(GameObject* target_)
{
	target = target_;
	//path = pf.FindPath(pos, target_->Pos());
	//GetNextNode();
}

//void Monster::GetNextNode()
//{
//	if ( path.size() == 0 )
//	{
//		path = pf.FindPath(pos, target->Pos());		
//	}
//	currentDest = path.front();
//
//	////add some randomness to currentDest so the enemies dont look like they are on rails
//	float xpos = (rand() % TERRAIN_W) - (TERRAIN_W / 2);
//	float ypos = (rand() % TERRAIN_W) - (TERRAIN_W / 2);
//	currentDest.pos = currentDest.pos + Vector2(xpos, ypos);
//
//	path.pop();
//}

//return up, down, left or right
Vector2 Monster::RandomiseDirection()
{
	Vector2 ret; 
	int num = rand() % 4; //number between 0 and 3 inclusive	
	ret.SetAngle(num * (PI / 2));
	return ret;
}




void Monster::RandomisePauseTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("PAUSE_TIME_MAX") - FileSettings::GetFloat("PAUSE_TIME_MIN");
    float r = random * diff;
	pauseTimeLimit = FileSettings::GetFloat("PAUSE_TIME_MIN") + r;
}

void Monster::RandomiseMovementTime()
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = FileSettings::GetFloat("MOVEMENT_TIMER_MAX") - FileSettings::GetFloat("MOVEMENT_TIMER_MIN");
    float r = random * diff;
    movementTimeLimit = FileSettings::GetFloat("MOVEMENT_TIMER_MIN") + r;
}

void Monster::ResetMovementDirection()
{
	direction = RandomiseDirection();
	RandomiseMovementTime();
	state = MONSTER_STATE::MOVING;	
}

void Monster::UndoUpdate()
{
	pos = previousPos;
}

//Use this Update method to swarm the player
//void Monster::Update(float delta_)
//{
//	if ( !active ) 
//		return;
//	
//	//move towards target
//	Vector2 direction = target->Pos() - pos;
//	direction.Normalise();
//	float deltaSpeed = speed * delta_;
//	direction.SetMagnitude(deltaSpeed); //monster speed
//	pos += direction;
//	MoveSprite(sprite, pos.x, pos.y);
//	RotateSpriteToVector(sprite, direction);
//}

void Monster::Update(float delta_)
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
		if ( distanceToPlayer <= FileSettings::GetFloat("SWARM_PLAYER_DISTANCE") )
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
			direction.SetMagnitude(deltaSpeed); //monster speed
			pos += direction;
		}
	}
}


//A* pathfinding Update method
//void Monster::Update(float delta_)
//{
//	if ( !active ) 
//		return;
//	
//	//do we need to get the next node from the queue? 
//	float distToNode = (currentDest.pos - pos).GetMagnitude();
//	if ( distToNode < 10.0f )
//		GetNextNode();
//	
//	//move towards target node
//	Vector2 direction = currentDest.pos - pos;
//	direction.Normalise();
//	float deltaSpeed = speed * delta_;
//	direction.SetMagnitude(deltaSpeed); //monster speed
//	pos += direction;
//	MoveSprite(sprite, pos.x, pos.y);
//	RotateSpriteToVector(sprite, direction);
//}

void Monster::Hit(int hit_ )
{
	health -= hit_;
	if ( health <= 0 )
	{
		active = false;
		DestroySprite(sprite);
	}
}

void Monster::Draw()
{
	if ( active ) 
	{
		MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		DrawSprite(sprite);
	}
}