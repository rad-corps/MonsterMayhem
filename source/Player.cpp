#include "Player.h"
#include "AIE.h"
#include "FrameworkHelpers.h"
#include "Enums.h"
#include "FileSettings.h"


Player::Player(void)
{
	width = PLAYER_W;
	height = PLAYER_H;
	sprite = CreateSprite ( "./images/Player_monster.png", width, height, true);
	pos = Vector2(BATTLE_FIELD_W/2, BATTLE_FIELD_H/2);
	timeSinceLoogie = 0.f;
	speed = PLAYER_SPEED;
	loogieReload = LOOGIE_RELOAD;
	active = true;
}


Player::~Player(void)
{
}

void Player::UndoUpdate()
{
	pos = previousPos;
}

void Player::Update(float delta_)
{	
	previousPos = pos;
	
	timeSinceLoogie += delta_;

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
	Vector2 dir = mouse - screenPos;	
	
	//calculate camera position
	Vector2 camAnchor(pos.x - SCREEN_W, pos.y - SCREEN_H);
	Vector2 camPos = (screenPos + mouse) / 2;
	camPos = camPos + camAnchor;

	//rotate player based on position and mouse
	float angle = dir.GetAngle();
	RotateSpriteToVector(sprite, dir);
	
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
	}
}

void Player::Draw()
{
	DrawSprite(sprite);
}

void Player::RegisterSpitObserver(SpitObserver* spitObserver_)
{
	spitObserver = spitObserver_;
}

void Player::EatPowerUp(PowerUp& powerUp)
{
	POWER_UP_TYPE type = powerUp.Eat();

	if ( type == POWER_UP_TYPE::SPEED_UP ) 
	{		
		speed *= 1.25f;
		if ( speed > FileSettings::GetFloat("MAX_PLAYER_SPEED") )
			speed = FileSettings::GetFloat("MAX_PLAYER_SPEED");
		cout << "SPEED = " << to_string(speed) << endl;
	}
	if ( type == POWER_UP_TYPE::SPIT_FREQUENCY ) 
	{		
		loogieReload *= 0.75f;
		if ( loogieReload < FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME") )
			loogieReload = FileSettings::GetFloat("MIN_SPIT_RELOAD_TIME");
		cout << "SPIT FREQUENCY = " << to_string(loogieReload) << endl;
	}
}