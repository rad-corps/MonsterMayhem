#include "Monster.h"
#include "FileSettings.h"

ExplosionObserver* Monster::explosionObserver = nullptr;

void Monster::RegisterTarget(GameObject* target_)
{
	target = target_;
}

void Monster::Hit(int hit_ )
{
	cout << "Monster::Hit()" << endl;
	health -= hit_;
	if ( health <= 0 )
	{
		active = false;
		explosionObserver->ExplosionEvent(pos, direction);
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

void Monster::RegisterExplosionObserver(ExplosionObserver* explosionObserver_)
{
	explosionObserver = explosionObserver_;
}

Monster::Monster(){}
Monster::~Monster(){}