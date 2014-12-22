//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// HitAnimation.cpp
/////////////////////////////////////////////////////////////////////////

#include "HitAnimation.h"
#include "AIE.h"

unsigned int HitAnimation::sprite = 0;

float HIT_1_UV[4] = { HIT_U_MIN             , HIT_V_MIN, HIT_U_MIN + HIT_U_STEP    , HIT_V_MIN + HIT_V_STEP };
float HIT_2_UV[4] = { HIT_U_MIN + HIT_U_STEP, HIT_V_MIN, HIT_U_MIN + HIT_U_STEP * 2, HIT_V_MIN + HIT_V_STEP };

HitAnimation::HitAnimation(Vector2 pos_)
{
	pos = pos_;
	width = 32;
	height = 32;
	//direction = direction_;

	float sprite_size[2] = { 32.0f, 32.0f };
	float origin[2] = { 16.0f, 16.0f };

	if ( sprite == 0 ) 
	{
		sprite = CreateSprite("./images/Explosion_hit_sprite_sheet.png", sprite_size, origin, HIT_1_UV);
	}
	active = true;

	animation = HIT_ANIMATION::HIT_ANIM_1;
	animationTimer = 0.0f;
}


HitAnimation::~HitAnimation(void)
{
}

void HitAnimation::Draw()
{
	if ( active ) 
	{
		if ( animation == HIT_ANIMATION::HIT_ANIM_1)
			SetSpriteUVCoordinates	( sprite, HIT_1_UV);
		if ( animation == HIT_ANIMATION::HIT_ANIM_2)
			SetSpriteUVCoordinates	( sprite, HIT_2_UV);

		MoveSprite(sprite, pos.x, pos.y);
		//RotateSpriteToVector(sprite, direction);
		//RotateSprite(sprite, 270.0f);
		DrawSprite(sprite);
	}
}

void HitAnimation::Update(float delta_)
{
	animationTimer += delta_;

	if ( animationTimer > 0.1f ) 
	{
		animationTimer = 0.0f;
		switch (animation)
		{
		case HIT_ANIMATION::HIT_ANIM_1: 
			animation = HIT_ANIMATION::HIT_ANIM_2;
			break;
		case HIT_ANIMATION::HIT_ANIM_2: 
			active = false;
			break;
		}
	}
}