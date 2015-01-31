//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Collision.cpp
/////////////////////////////////////////////////////////////////////////

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

	//calculate a slight reduction in radius to account for some collision overlap
	float obj1_radius = obj1_->Width() / 2;
	float obj2_radius = obj2_->Width() / 2;
	obj1_radius *= 0.7f;
	obj2_radius *= 0.7f;

	float distance = sqrt(pow(obj1_->Pos().x - obj2_->Pos().x, 2) + pow(obj1_->Pos().y - obj2_->Pos().y, 2));
	if ( distance < obj1_radius + obj2_radius )
		return true;
	return false;
}

//check rectangle collision between two rectangles
bool Collision::RectCollision(Rect r1_, Rect r2_, float scale_)
{
	r1_.Scale(scale_);
	r2_.Scale(scale_);

	if (r1_.Right() < r2_.Left() 
		|| r2_.Right() < r1_.Left() 
		|| r1_.Bottom() > r2_.Top() 
		|| r1_.Top() < r2_.Bottom())
		
		return false;
	return true;
}