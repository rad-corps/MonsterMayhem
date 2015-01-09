//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Player.cpp
/////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "AIE.h"
#include "FrameworkHelpers.h"
#include "Enums.h"
#include "FileSettings.h"
#include "Sound.h"

//UV coordinates
float PLAYER_STATIONARY_UV[4] = { PLAYER_U_MIN                   , PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP    , PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_MOVEMENT1_UV[4] = { PLAYER_U_MIN + PLAYER_U_STEP    , PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 2, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_MOVEMENT2_UV[4] = { PLAYER_U_MIN + PLAYER_U_STEP * 2, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 3, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT1_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 3, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 4, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT2_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 4, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 5, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT3_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 5, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 6, PLAYER_V_MIN + PLAYER_V_STEP };

float PLAYER_DEATH1_UV[4] =	   { P_DEATH_U_MIN				       , P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP    , P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH2_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP    , P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 2, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH3_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 2, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 3, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH4_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 3, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 4, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH5_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 4, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 5, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH6_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 5, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 6, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH7_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 6, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 7, P_DEATH_V_MIN + P_DEATH_V_STEP};
float PLAYER_DEATH8_UV[4] =	   { P_DEATH_U_MIN + P_DEATH_U_STEP * 7, P_DEATH_V_MIN, P_DEATH_U_MIN + P_DEATH_U_STEP * 8, P_DEATH_V_MIN + P_DEATH_V_STEP};

/// Non-scalable way
PLAYER_ANIMATION& operator++(PLAYER_ANIMATION& f)
{
    switch(f)
    {
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH1: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH2;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH2: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH3;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH3: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH4;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH4: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH5;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH5: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH6;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH6: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH7;
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH7: return f = PLAYER_ANIMATION::PLAYER_ANIM_DEATH8;		
		case PLAYER_ANIMATION::PLAYER_ANIM_DEATH8: return f = PLAYER_ANIMATION::PLAYER_DEATH_ANIM_FINISHED;		
    }
}

//must call non default constructor 
Player::Player()
{
	width = PLAYER_W;
	height = PLAYER_H;

	//pos = pos_;
	//pos = Vector2(BATTLE_FIELD_W/2, BATTLE_FIELD_H/2);
	

	float sprite_size[2] = { 64.0f, 64.0f };
	float origin[2] = { 32.0f, 32.0f };
	
	//float uv[4] = { PLAYER_U_MIN, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP, PLAYER_V_MIN + PLAYER_V_STEP};

	//sprite = CreateSprite ( "./images/Character_sprite_sheet.png", sprite_size, origin, uv);
	sprite = CreateSprite ( "./images/Character_sprite_sheet.png", sprite_size, origin, PLAYER_STATIONARY_UV);
	deathSprite = CreateSprite ( "./images/player_death_sprite_sheet.png", sprite_size, origin, PLAYER_STATIONARY_UV);	

	//sprite = CreateSprite ( "./images/Character_sprite_sheet.png", 512, 320, false);
	
	timeSinceLoogie = 0.f;
	speed = PLAYER_SPEED;
	loogieReload = LOOGIE_RELOAD;
	active = true;

	animationTimer = 0.0f;
	status = PLAYER_STATUS::PLAYER_STATIONARY;

	//Have some breakfast before fighting monsters
	PowerUp p1;
	PowerUp p2;
	p1.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY, pos);
	p2.Spawn(POWER_UP_TYPE::SPEED_UP, pos);
	EatPowerUp(p1);
	EatPowerUp(p2);
	inMud = false;
	alive = true;
}

Player::Player(Vector2 pos_)
{
	


}


Player::~Player(void)
{
}

void Player::Die()
{
	alive = false;
	animation = PLAYER_ANIMATION::PLAYER_ANIM_DEATH1;
	animationTimer = 0.0f;
}

bool Player::Alive()
{
	return alive;
}

bool Player::DeathAnimationFinished()
{
	return animation == PLAYER_ANIMATION::PLAYER_DEATH_ANIM_FINISHED;
}

void Player::SetPlayerPos(int tileX_, int tileY_)
{
	//get the pos from the level data

	//invert the Y
	int tileY = FileSettings::GetInt("TERRAIN_ROWS") - tileY_;
	pos.x = tileX_ * TERRAIN_W;
	pos.y = tileY * TERRAIN_H;
}

void Player::UndoUpdate()
{
	pos = previousPos;
}

void Player::SetInMud(bool inMud_)
{
	inMud = inMud_;
}

void Player::UpdateXMovement(float delta_)
{
	if ( !alive ) 
		return;

	previousPos = pos;
	float costMutliplyer = 1.0f;
	if (inMud )
		costMutliplyer /= 2;

	float staminaReduction = FileSettings::GetFloat("STAMINA_REDUCER") * delta_;

	if ( IsKeyDown(KEY_A) )
	{
		pos.x -= speed * delta_ * costMutliplyer;
		//pos += direction.Rotate90(false) * (speed * delta_);
		speed -= staminaReduction;
	}
	if ( IsKeyDown(KEY_D) )
	{
		pos.x += speed * delta_ * costMutliplyer;
		//pos += direction.Rotate90(true) * (speed * delta_);
		speed -= staminaReduction;
	}
}

void Player::UpdateYMovement(float delta_)
{
	if ( !alive ) 
		return;

	previousPos = pos;

	float costMutliplyer = 1.0f;
	if (inMud )
		costMutliplyer /= 2;

	float staminaReduction = FileSettings::GetFloat("STAMINA_REDUCER") * delta_;

	//handle user input
	if ( IsKeyDown(KEY_W) )
	{
		pos.y += speed * delta_ * costMutliplyer;
		//pos += direction * (speed * delta_);
		speed -= staminaReduction;	
	}
	if ( IsKeyDown(KEY_S) )
	{
		pos.y -= speed * delta_ * costMutliplyer;
		//pos -= direction * (speed * delta_);
		speed -= staminaReduction;
	}
}

void Player::Update(float delta_)
{	
	animationTimer += delta_;
	
	if (!alive)
	{
		if ( animationTimer > 0.2f ) 
		{
			animationTimer = 0.0f;
			animation++;

			//todo check for animation complete. 
		}

		return;
	}

	timeSinceLoogie += delta_;
	

	if ( status == PLAYER_STATUS::PLAYER_SPITTING ) 
	{
		if ( animationTimer > 0.06f ) 
		{
			animationTimer = 0.0f;
			switch (animation)
			{
			case PLAYER_ANIMATION::PLAYER_ANIM_SPITTING1 : 
				animation = PLAYER_ANIMATION::PLAYER_ANIM_SPITTING2;
			    break;
			case PLAYER_ANIMATION::PLAYER_ANIM_SPITTING2 : 
				animation = PLAYER_ANIMATION::PLAYER_ANIM_SPITTING3;
			    break;
			case PLAYER_ANIMATION::PLAYER_ANIM_SPITTING3 : 
				status = PLAYER_STATUS::PLAYER_STATIONARY;
			    break;
			}
		}
	}
	
	if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D) )
	{
		if ( animationTimer > 0.2f ) 
		{
			animationTimer = 0.0f;
			if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_WALKING1)
			{
				animation = PLAYER_ANIMATION::PLAYER_ANIM_WALKING2;
			}
			else if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_WALKING2)
			{
				animation = PLAYER_ANIMATION::PLAYER_ANIM_WALKING1;
			}
		}

		if  (status == PLAYER_STATUS::PLAYER_STATIONARY)
		{
			status = PLAYER_STATUS::PLAYER_MOVING;
			animationTimer = 0.0f;
			animation = PLAYER_ANIMATION::PLAYER_ANIM_WALKING1;
		}
	}
	else if ( status != PLAYER_STATUS::PLAYER_SPITTING )
	{
		animation = PLAYER_ANIMATION::PLAYER_ANIM_STATIONARY;
		status = PLAYER_STATUS::PLAYER_STATIONARY;
	}
	
	//dont let our player get below the min speed
	if ( speed < FileSettings::GetFloat("MIN_PLAYER_SPEED") )
	{
		speed = FileSettings::GetFloat("MIN_PLAYER_SPEED");
	}
	
	//get the mouse coordinate. use our own function as the AIE one is inverted
	GetMouseLocationEx(mouseX, mouseY, FileSettings::GetInt("SCREEN_H"));

	//get the variables needed to calc player pos, rotation and camera pos. 
	Vector2 screenPos = GetGameObjectScreenPosition(pos);
	Vector2 mouse(mouseX, mouseY);
	direction = mouse - screenPos;	
	direction.Normalise();
	
	//calculate camera position
	Vector2 camAnchor(pos.x - FileSettings::GetInt("SCREEN_W"), pos.y - FileSettings::GetInt("SCREEN_H"));
	Vector2 camPos = (screenPos + mouse) / 2;
	camPos = camPos + camAnchor;

	//rotate player based on position and mouse
	float angle = direction.GetAngle();
	
	//move the player and the camera
	MoveSprite(sprite, pos.x, pos.y);
	MoveCamera(camPos.x, camPos.y);	

	//	check for spit ... ewww
	if ( GetMouseButtonDown(0) && timeSinceLoogie > loogieReload )
	{		
		//reduce saliva
		loogieReload += FileSettings::GetFloat("SALIVA_REDUCER");
		
		//dont let saliva get too low
		if ( loogieReload > FileSettings::GetFloat("MAX_SPIT_RELOAD_TIME") )
			loogieReload = FileSettings::GetFloat("MAX_SPIT_RELOAD_TIME");

		//reset timer 
		timeSinceLoogie = 0.0f;
		
		//tell the observer (PSGameLoop) to create a spit
		spitObserver->SpitEvent(pos, angle, 1.0f);
		animation = PLAYER_ANIMATION::PLAYER_ANIM_SPITTING1;
		status = PLAYER_STATUS::PLAYER_SPITTING;
		animationTimer = 0.0f;
	}

	CalcGUIBars();
}

void Player::CalcGUIBars()
{
	//float saliva = FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME") / loogieReload;
	//float stamina = speed / FileSettings::GetFloat("MAX_PLAYER_SPEED");	

	float saliva = FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME") / loogieReload;

	float stamina = (speed - FileSettings::GetFloat("MIN_PLAYER_SPEED")) /
		(FileSettings::GetFloat("MAX_PLAYER_SPEED") - FileSettings::GetFloat("MIN_PLAYER_SPEED") );

	//cout << saliva << endl;
	//cout << "saliva: " << saliva << "\tstamina: " << stamina << endl;

	playerObserver->UpdatePlayerGUI(saliva, stamina);
	
}

void Player::Draw()
{
	if ( alive ) 
	{
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_STATIONARY)
			SetSpriteUVCoordinates	( sprite, PLAYER_STATIONARY_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_WALKING1)
			SetSpriteUVCoordinates	( sprite, PLAYER_MOVEMENT1_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_WALKING2)
			SetSpriteUVCoordinates	( sprite, PLAYER_MOVEMENT2_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_SPITTING1)
			SetSpriteUVCoordinates	( sprite, PLAYER_SPIT1_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_SPITTING2)
			SetSpriteUVCoordinates	( sprite, PLAYER_SPIT2_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_SPITTING3)
			SetSpriteUVCoordinates	( sprite, PLAYER_SPIT3_UV);

		RotateSpriteToVector(sprite, direction);
		RotateSprite(sprite, 270.0f);
		DrawSprite(sprite);
	}
	else
	{
		//draw death animation
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH1 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH1_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH2 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH2_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH3 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH3_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH4 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH4_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH5 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH5_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH6 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH6_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH7 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH7_UV);
		if ( animation == PLAYER_ANIMATION::PLAYER_ANIM_DEATH8 )
			SetSpriteUVCoordinates	( deathSprite, PLAYER_DEATH8_UV);
		MoveSprite(deathSprite, pos.x, pos.y);
		RotateSpriteToVector(deathSprite, direction);
		RotateSprite(deathSprite, 270.0f);
		DrawSprite(deathSprite);
	}
}

void Player::RegisterSpitObserver(SpitObserver* spitObserver_)
{
	spitObserver = spitObserver_;
}

void Player::RegisterPlayerObserver(PlayerObserver* playerObserver_)
{
	playerObserver = playerObserver_;
}

void Player::EatPowerUp(PowerUp& powerUp)
{
	POWER_UP_TYPE type = powerUp.Eat();

	if ( type == POWER_UP_TYPE::SPEED_UP )
		Sound::PlayGameSound(SOUNDS::STAMINA_UP);
	else if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
		Sound::PlayGameSound(SOUNDS::SPIT_UP);

	if ( type == POWER_UP_TYPE::SPEED_UP ) 
	{		
		speed *= FileSettings::GetFloat("SPEED_INCREASER");
		if ( speed > FileSettings::GetFloat("MAX_PLAYER_SPEED") )
			speed = FileSettings::GetFloat("MAX_PLAYER_SPEED");
		cout << "SPEED = " << to_string(speed) << endl;
	}
	if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
	{		
		loogieReload *= FileSettings::GetFloat("SPIT_RELOAD_DECREASER");
		if ( loogieReload < FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME") )
			loogieReload = FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME");
		cout << "SPIT FREQUENCY = " << to_string(loogieReload) << endl;
	}
}