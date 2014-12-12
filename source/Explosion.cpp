#include "Explosion.h"
#include "AIE.h"
#include "Enums.h"
#include "FrameworkHelpers.h"

unsigned int Explosion::sprite = 0;

float EXPLOSION_1_UV[4] = { EXPLOSION_U_MIN                      , EXPLOSION_V_MIN, EXPLOSION_U_MIN + EXPLOSION_U_STEP    , EXPLOSION_V_MIN + EXPLOSION_V_STEP };
float EXPLOSION_2_UV[4] = { EXPLOSION_U_MIN + EXPLOSION_U_STEP   , EXPLOSION_V_MIN, EXPLOSION_U_MIN + EXPLOSION_U_STEP * 2, EXPLOSION_V_MIN + EXPLOSION_V_STEP };
float EXPLOSION_3_UV[4] = { EXPLOSION_U_MIN + EXPLOSION_U_STEP *2, EXPLOSION_V_MIN, EXPLOSION_U_MIN + EXPLOSION_U_STEP * 3, EXPLOSION_V_MIN + EXPLOSION_V_STEP };
float EXPLOSION_4_UV[4] = { EXPLOSION_U_MIN + EXPLOSION_U_STEP *3, EXPLOSION_V_MIN, EXPLOSION_U_MIN + EXPLOSION_U_STEP * 4, EXPLOSION_V_MIN + EXPLOSION_V_STEP };

Explosion::Explosion(Vector2 pos_, Vector2 direction_)
{
	pos = pos_;
	width = 64;
	height = 64;
	direction = direction_;

	float sprite_size[2] = { 64.0f, 64.0f };
	float origin[2] = { 32.0f, 32.0f };

	if ( sprite == 0 ) 
	{
		sprite = CreateSprite("./images/Explosion_death_sprite_sheet.png", sprite_size, origin, EXPLOSION_1_UV);
	}
	active = true;

	animation = EXPLOSION_ANIMATION::EXP_ANIM_1;
	animationTimer = 0.0f;
}


Explosion::~Explosion(void)
{
}

void Explosion::Draw()
{
	if ( active ) 
	{
		if ( animation == EXPLOSION_ANIMATION::EXP_ANIM_1)
			SetSpriteUVCoordinates	( sprite, EXPLOSION_1_UV);
		if ( animation == EXPLOSION_ANIMATION::EXP_ANIM_2)
			SetSpriteUVCoordinates	( sprite, EXPLOSION_2_UV);
		if ( animation == EXPLOSION_ANIMATION::EXP_ANIM_3)
			SetSpriteUVCoordinates	( sprite, EXPLOSION_3_UV);
		if ( animation == EXPLOSION_ANIMATION::EXP_ANIM_4)
			SetSpriteUVCoordinates	( sprite, EXPLOSION_4_UV);

		MoveSprite(sprite, pos.x, pos.y);
		RotateSpriteToVector(sprite, direction);
		RotateSprite(sprite, 270.0f);
		DrawSprite(sprite);
	}
}

void Explosion::Update(float delta_)
{
	animationTimer += delta_;

	if ( animationTimer > 0.2f ) 
	{
		animationTimer = 0.0f;
		switch (animation)
		{
		case EXPLOSION_ANIMATION::EXP_ANIM_1 : 
			animation = EXPLOSION_ANIMATION::EXP_ANIM_2;
			break;
		case EXPLOSION_ANIMATION::EXP_ANIM_2 : 
			animation = EXPLOSION_ANIMATION::EXP_ANIM_3;
			break;
		case EXPLOSION_ANIMATION::EXP_ANIM_3 : 
			animation = EXPLOSION_ANIMATION::EXP_ANIM_4;
			break;
		case EXPLOSION_ANIMATION::EXP_ANIM_4 : 
			active = false;
			break;
		}
	}
}