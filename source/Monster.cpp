#include "Monster.h"
#include "AIE.h"
#include <iostream>
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "PathFinder.h"

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
			speed = 100.f;
			sprite = CreateSprite("./images/Monster_Medium.png", width, height, true);
			break;
		case MONSTER_TYPE::LARGE : 
			width = 64;
			height = 64;
			health = 20;
			speed = 133.f;
			sprite = CreateSprite("./images/Monster_Large.png", width, height, true);
			break;
		case MONSTER_TYPE::BOSS: 
			width = 128;
			height = 128;
			health = 40;
			speed = 200.f;
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
	path = pf.FindPath(pos, target_->Pos());
	GetNextNode();
}

void Monster::GetNextNode()
{
	if ( path.size() == 0 )
	{
		path = pf.FindPath(pos, target->Pos());		
	}
	currentDest = path.front();

	////add some randomness to currentDest so the enemies dont look like they are on rails
	float xpos = (rand() % TERRAIN_W) - (TERRAIN_W / 2);
	float ypos = (rand() % TERRAIN_W) - (TERRAIN_W / 2);
	currentDest.pos = currentDest.pos + Vector2(xpos, ypos);

	path.pop();
}


//void Monster::Update(float delta_)
//{
//	if ( !active ) 
//		return;
//	
//	//move towards target
//	Vector2 direction = target->Pos() - pos;
//	direction.Normalise();
//	float deltaSpeed = speed * delta_;
//	direction.SetMagnitude(deltaSpeed); //monster speed
//	pos += direction;
//	MoveSprite(sprite, pos.x, pos.y);
//	RotateSpriteToVector(sprite, direction);
//}

void Monster::Update(float delta_)
{
	if ( !active ) 
		return;
	
	//do we need to get the next node from the queue? 
	float distToNode = (currentDest.pos - pos).GetMagnitude();
	if ( distToNode < 10.0f )
		GetNextNode();
	
	//move towards target node
	Vector2 direction = currentDest.pos - pos;
	direction.Normalise();
	float deltaSpeed = speed * delta_;
	direction.SetMagnitude(deltaSpeed); //monster speed
	pos += direction;
	MoveSprite(sprite, pos.x, pos.y);
	RotateSpriteToVector(sprite, direction);
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