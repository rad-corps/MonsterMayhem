#include "Monster.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"

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
			sprite = CreateSprite("./images/Monster_Medium.png", width, height, true);
			break;
		case MONSTER_TYPE::LARGE : 
			width = 64;
			height = 64;
			health = 30;
			sprite = CreateSprite("./images/Monster_Large.png", width, height, true);
			break;
		case MONSTER_TYPE::BOSS: 
			width = 128;
			height = 128;
			health = 100;
			sprite = CreateSprite("./images/Monster_Boss.png", width, height, true);
			break;
	}
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
		DrawSprite(sprite);
}