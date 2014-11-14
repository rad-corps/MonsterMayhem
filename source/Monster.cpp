#include "Monster.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"

using namespace std;


Monster::Monster(void)
{
	//randomise a position
	int xPos = rand() % BATTLE_FIELD_W;
	int yPos = rand() % BATTLE_FIELD_H;

	width = 32;
	height = 32;

	pos = Vector2(xPos,yPos);
	sprite = CreateSprite("./images/Monster_Medium.png", 32, 32, true);
	active = true;

}


Monster::~Monster(void)
{
}

void Monster::RegisterTarget(GameObject* target_)
{
	target = target_;
}


void Monster::Update(float delta_)
{
	if ( !active ) 
		return;
	
	//move towards target

	//player pos:
	//target->pos;
	Vector2 direction = target->Pos() - pos;
	direction.Normalise();
	float speed = 100.0f * delta_;
	direction.SetMagnitude(speed); //monster speed
	pos += direction;
	MoveSprite(sprite, pos.x, pos.y);
	
}

void Monster::Hit(float hit_ )
{
	active = false;
}

void Monster::Draw()
{
	if ( active ) 
		DrawSprite(sprite);
}