#include "Collision.h"
#include <iostream>

using namespace std;

Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}

//circle collision between two gameobjects
bool Collision::CheckCollision(GameObject* obj1_, GameObject* obj2_)
{
	if ( !obj1_->IsActive() || !obj2_->IsActive() )
		return false;

	float distance = sqrt(pow(obj1_->Pos().x - obj2_->Pos().x, 2) + pow(obj1_->Pos().y - obj2_->Pos().y, 2));
	if ( distance < obj1_->Width() / 2 + obj2_->Width() /2 )
		return true;
	return false;
}

//check rectangle collision between two rectangles
bool Collision::RectCollision(Rect r1_, Rect r2_)
{
	if (r1_.Right() < r2_.Left() 
		|| r2_.Right() < r1_.Left() 
		|| r1_.Bottom() > r2_.Top() 
		|| r1_.Top() < r2_.Bottom())
		
		return false;
	return true;
}