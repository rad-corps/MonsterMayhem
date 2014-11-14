#include "Player.h"
#include "AIE.h"
#include "FrameworkHelpers.h"
#include "Enums.h"


Player::Player(void)
{
	width = PLAYER_W;
	height = PLAYER_H;
	sprite = CreateSprite ( "./images/Player_monster.png", width, height, true);
	pos = Vector2(BATTLE_FIELD_W/2, BATTLE_FIELD_H/2);
	timeSinceLoogie = 0.f;
}


Player::~Player(void)
{
}

void Player::Update(float delta_)
{	
	timeSinceLoogie += delta_;

	//handle user input
	if ( IsKeyDown(KEY_W) )
	{
		pos.y += PLAYER_SPEED * delta_;
	}
	if ( IsKeyDown(KEY_S) )
	{
		pos.y -= PLAYER_SPEED * delta_;
	}
	if ( IsKeyDown(KEY_A) )
	{
		pos.x -= PLAYER_SPEED * delta_;
	}
	if ( IsKeyDown(KEY_D) )
	{
		pos.x += PLAYER_SPEED * delta_;
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
	if ( GetMouseButtonDown(0) && timeSinceLoogie > LOOGIE_RELOAD )
	{
		timeSinceLoogie = 0.0f;
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