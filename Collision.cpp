#include "Collision.h"
#include <iostream>

using namespace std;

Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}

bool Collision::CheckCollision(GameObject* obj1_, GameObject* obj2_)
{
	if ( !obj1_->IsActive() || !obj2_->IsActive() )
		return false;

	float distance = sqrt(pow(obj1_->Pos().x - obj2_->Pos().x, 2) + pow(obj1_->Pos().y - obj2_->Pos().y, 2));
	if ( distance < obj1_->Width() / 2 + obj2_->Width() /2 )
		return true;
	return false;
}