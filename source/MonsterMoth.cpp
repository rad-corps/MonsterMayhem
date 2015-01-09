//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// MonsterMoth.cpp
/////////////////////////////////////////////////////////////////////////

#include "MonsterMoth.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"
#include "FileSettings.h"

float MOVEMENT1_UV[4] = { MOTH_U_MIN                      , MOTH_V_MIN  , MOTH_U_MIN +   MOTH_U_STEP    , MOTH_V_MIN + MOTH_V_STEP };
float MOVEMENT2_UV[4] = { MOTH_U_MIN + MOTH_U_STEP        , MOTH_V_MIN  , MOTH_U_MIN +   MOTH_U_STEP * 2, MOTH_V_MIN + MOTH_V_STEP };                        
float MOVEMENT3_UV[4] = { MOTH_U_MIN + MOTH_U_STEP     * 2, MOTH_V_MIN  , MOTH_U_MIN +   MOTH_U_STEP * 3, MOTH_V_MIN + MOTH_V_STEP };
float HIT_UV[4] =       { MOTH_U_MIN + MOTH_U_STEP     * 3, MOTH_V_MIN  , MOTH_U_MIN +   MOTH_U_STEP * 4, MOTH_V_MIN + MOTH_V_STEP };


using namespace std;

unsigned int MonsterMoth::sprite = 0;

MonsterMoth::MonsterMoth(Vector2 pos_)
{
	pos = pos_;
	//default width and height for enemies
	width = 64;
	height = 64;
	health = 20;
	score = 30;

	float sprite_size[2] = { 64.0f, 64.0f };
	float origin[2] = { 32.0f, 32.0f };


	
	//only create the sprite once.
	if ( sprite == 0 )
		sprite = CreateSprite ( "./images/Character_sprite_sheet.png", sprite_size, origin, MOVEMENT1_UV);
		//sprite = CreateSprite("./images/Character_sprite_sheet.png", width, height, true);

	active = true;

	distTravelledSinceDirectionCalc = 0.0f;
	RandomiseInitialDirection();
	velocity.SetAngle(direction.GetAngle());

	animationTimer = 0.0f;
	animation = MOTH_ANIMATION::MOTH_ANIM_MOVE1;
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

void MonsterMoth::Hit(int power_)
{
	Monster::Hit(power_);
	animation = MOTH_ANIMATION::MOTH_ANIM_HIT;
	animationTimer = 0.0f;
}

void MonsterMoth::Update(float delta_)
{

	Vector2 previousPos = pos;

	animationTimer += delta_;

	if ( animation == MOTH_ANIMATION::MOTH_ANIM_HIT && animationTimer > 1.0f )
	{
		animation = MOTH_ANIMATION::MOTH_ANIM_MOVE1;
	}
	else if ( animationTimer > 0.2f && animation != MOTH_ANIMATION::MOTH_ANIM_HIT )
	{
		animationTimer = 0.0f;
		switch ( animation ) 
		{
		case MOTH_ANIMATION::MOTH_ANIM_MOVE1 :
			animation = MOTH_ANIMATION::MOTH_ANIM_MOVE2;
			break;
		case MOTH_ANIMATION::MOTH_ANIM_MOVE2 :
			animation = MOTH_ANIMATION::MOTH_ANIM_MOVE3;
			break;
		case MOTH_ANIMATION::MOTH_ANIM_MOVE3 :
			animation = MOTH_ANIMATION::MOTH_ANIM_MOVE4;
			break;
		case MOTH_ANIMATION::MOTH_ANIM_MOVE4 :
			animation = MOTH_ANIMATION::MOTH_ANIM_MOVE1;
			break;
		case MOTH_ANIMATION::MOTH_ANIM_HIT :
			animation = MOTH_ANIMATION::MOTH_ANIM_MOVE1;
			break;
		}
	}
	
	if ( pos.x < 0 || pos.x > FileSettings::GetInt("BATTLE_FIELD_W") )
	{
		velocity.x = -(velocity.x);
		direction.x = -(direction.x);
	}
	if ( pos.y < 0 || pos.y > FileSettings::GetInt("BATTLE_FIELD_H") )
	{
		velocity.y = -(velocity.y);
		direction.y = -(direction.y);
	}
	
	if ( animation != MOTH_ANIMATION::MOTH_ANIM_HIT ) 
	{
		if ( CanSeePlayer() )
		{
			direction = (target->Pos() - pos ).GetNormal();
		}
	}
	
	if ( animation != MOTH_ANIMATION::MOTH_ANIM_HIT ) 
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
		if ( animation == MOTH_ANIMATION::MOTH_ANIM_MOVE1)
			SetSpriteUVCoordinates	( sprite, MOVEMENT1_UV);
		if ( animation == MOTH_ANIMATION::MOTH_ANIM_MOVE2 || animation == MOTH_ANIMATION::MOTH_ANIM_MOVE4)
			SetSpriteUVCoordinates	( sprite, MOVEMENT2_UV);
		if ( animation == MOTH_ANIMATION::MOTH_ANIM_MOVE3)
			SetSpriteUVCoordinates	( sprite, MOVEMENT3_UV);
		if ( animation == MOTH_ANIMATION::MOTH_ANIM_HIT)
			SetSpriteUVCoordinates	( sprite, HIT_UV);

		//MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		RotateSprite(sprite, 270.0f);
		//DrawSprite(sprite);
		DrawIfOnScreen(sprite, pos.x, pos.y);
	}
}

//ignore terrain collision for flying monsters
void MonsterMoth::HandleTerrainCollision()
{
}