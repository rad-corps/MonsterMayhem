#include "Monster.h"
#include "FileSettings.h"

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

bool Monster::CanSeePlayer()
{
	//are we within the enemy seeing distance? 
	float distanceToPlayer = (target->Pos() - pos).GetMagnitude();		
	if ( distanceToPlayer > FileSettings::GetFloat("SWARM_PLAYER_DISTANCE") )
		return false;

	//is the player within our cone? 
	Vector2 directionToPlayer = (target->Pos() - pos).GetNormal();
	Vector2 enemyFacing = direction.GetNormal();
	float difference = enemyFacing.AngleBetweenVectors(directionToPlayer);
	if ( difference > FileSettings::GetFloat("ENEMY_VIEW_FRUSTRUM") ) 
		return false;

	return true;
}

Monster::Monster(){}
Monster::~Monster(){}