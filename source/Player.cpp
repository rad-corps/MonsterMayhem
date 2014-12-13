#include "Player.h"
#include "AIE.h"
#include "FrameworkHelpers.h"
#include "Enums.h"
#include "FileSettings.h"

float PLAYER_STATIONARY_UV[4] = { PLAYER_U_MIN                   , PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP    , PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_MOVEMENT1_UV[4] = { PLAYER_U_MIN + PLAYER_U_STEP    , PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 2, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_MOVEMENT2_UV[4] = { PLAYER_U_MIN + PLAYER_U_STEP * 2, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 3, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT1_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 3, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 4, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT2_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 4, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 5, PLAYER_V_MIN + PLAYER_V_STEP };
float PLAYER_SPIT3_UV[4] =     { PLAYER_U_MIN + PLAYER_U_STEP * 5, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP * 6, PLAYER_V_MIN + PLAYER_V_STEP };

Player::Player(void)
{
	width = PLAYER_W;
	height = PLAYER_H;
	

	float sprite_size[2] = { 64.0f, 64.0f };
	float origin[2] = { 32.0f, 32.0f };
	//float uv[4] = { PLAYER_U_MIN, PLAYER_V_MIN, PLAYER_U_MIN + PLAYER_U_STEP, PLAYER_V_MIN + PLAYER_V_STEP};

	//sprite = CreateSprite ( "./images/Character_sprite_sheet.png", sprite_size, origin, uv);
	sprite = CreateSprite ( "./images/Character_sprite_sheet.png", sprite_size, origin, PLAYER_STATIONARY_UV);

	//sprite = CreateSprite ( "./images/Character_sprite_sheet.png", 512, 320, false);
	pos = Vector2(BATTLE_FIELD_W/2, BATTLE_FIELD_H/2);
	timeSinceLoogie = 0.f;
	speed = PLAYER_SPEED;
	loogieReload = LOOGIE_RELOAD;
	active = true;

	animationTimer = 0.0f;
	status = PLAYER_STATUS::PLAYER_STATIONARY;
}


Player::~Player(void)
{
}

void Player::UndoUpdate()
{
	pos = previousPos;
}

void Player::UpdateXMovement(float delta_)
{
	previousPos = pos;

	float staminaReduction = FileSettings::GetFloat("STAMINA_REDUCER") * delta_;

	if ( IsKeyDown(KEY_A) )
	{
		pos.x -= speed * delta_;
		speed -= staminaReduction;
	}
	if ( IsKeyDown(KEY_D) )
	{
		pos.x += speed * delta_;
		speed -= staminaReduction;
	}
}

void Player::UpdateYMovement(float delta_)
{
	previousPos = pos;

	float staminaReduction = FileSettings::GetFloat("STAMINA_REDUCER") * delta_;

	//handle user input
	if ( IsKeyDown(KEY_W) )
	{
		pos.y += speed * delta_;
		speed -= staminaReduction;	
	}
	if ( IsKeyDown(KEY_S) )
	{
		pos.y -= speed * delta_;
		speed -= staminaReduction;
	}
}

void Player::Update(float delta_)
{	
	
	timeSinceLoogie += delta_;
	animationTimer += delta_;

	

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
	
	//get the mouse coordinate. used our own function as AIE one is inverted
	GetMouseLocationEx(mouseX, mouseY, SCREEN_H);

	//get the variables needed to calc player pos, rotation and camera pos. 
	Vector2 screenPos = GetGameObjectScreenPosition(pos);
	Vector2 mouse(mouseX, mouseY);
	direction = mouse - screenPos;	
	
	//calculate camera position
	Vector2 camAnchor(pos.x - SCREEN_W, pos.y - SCREEN_H);
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
	float saliva = FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME") / loogieReload;
	float stamina = speed / FileSettings::GetFloat("MAX_PLAYER_SPEED");	
	playerObserver->UpdatePlayerGUI(saliva, stamina);
}

void Player::Draw()
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