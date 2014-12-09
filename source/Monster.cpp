#include "Monster.h"

void Monster::RegisterTarget(GameObject* target_)
{
	target = target_;
}

void Monster::Hit(int hit_ )
{
	health -= hit_;
	if ( health <= 0 )
	{
		active = false;
		//DestroySprite(sprite);
	}
}

Monster::Monster(){}
Monster::~Monster(){}