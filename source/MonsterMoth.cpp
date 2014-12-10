#include "MonsterMoth.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

using namespace std;

unsigned int MonsterMoth::sprite = 0;

MonsterMoth::MonsterMoth(Vector2 pos_)
{
	pos = pos_;
	//default width and height for enemies
	width = 64;
	height = 64;
	health = 10;
	
	//only create the sprite once.
	if ( sprite == 0 )
		sprite = CreateSprite("./images/Monster_Moth.png", width, height, true);

	active = true;

	distTravelledSinceDirectionCalc = 0.0f;
	RandomiseInitialDirection();
	velocity.SetAngle(direction.GetAngle());	
}

//return up, down, left or right
void MonsterMoth::RandomiseInitialDirection()
{	
	int num = rand() % 4; //number between 0 and 3 inclusive	
	direction.SetAngle(num * (PI / 2));
}

//either 45d acw 45deg cw or 0
void MonsterMoth::RandomiseNewDirection()
{
	int num = rand() % 3; //0,1,2
	float angle = num * (PI / 4); //PI / 4 is a quarter of a half circle
	angle -= PI / 4;
	direction.SetAngle(direction.GetAngle() + angle);
}

MonsterMoth::~MonsterMoth(void)
{
	
}

void MonsterMoth::Update(float delta_)
{

	Vector2 previousPos = pos;
	
	if ( pos.x < 0 || pos.x > BATTLE_FIELD_W )
	{
		velocity.x = -(velocity.x);
		direction.x = -(direction.x);
	}
	if ( pos.y < 0 || pos.y > BATTLE_FIELD_H )
	{
		velocity.y = -(velocity.y);
		direction.y = -(direction.y);
	}
	
	if ( CanSeePlayer() )
	{
		direction = (target->Pos() - pos ).GetNormal();
	}
	
	velocity += direction * MOTH_ACCEL * delta_;

	if ( velocity.GetMagnitude() > MOTH_MAX_SPEED )
		velocity.SetMagnitude(MOTH_MAX_SPEED);

	pos += velocity * delta_;

	
	if ( !CanSeePlayer() )
	{
		distTravelledSinceDirectionCalc += (pos - previousPos).GetMagnitude();

		if ( distTravelledSinceDirectionCalc > TERRAIN_W )
		{
			distTravelledSinceDirectionCalc = 0.0f;
			RandomiseNewDirection();
		}
	}
	
}


void MonsterMoth::Draw()
{
	if ( active ) 
	{
		MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		DrawSprite(sprite);
	}
}

//ignore terrain collision for flying monsters
void MonsterMoth::HandleTerrainCollision()
{
}