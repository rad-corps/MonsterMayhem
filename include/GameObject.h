//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// GameObject.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"
#include "Rect.h"

class GameObject
{
public:
	GameObject(void);
	
	//destructor must be virtual to ensure it is called
	virtual ~GameObject(void);

	//pure virtuals
	virtual void Update(float delta_) = 0;
	virtual void Draw() = 0;

	float Width();
	float Height();

	bool IsActive();
	void SetActive(bool active_);
	Vector2 Pos();

	Rect GetRect();

protected:
	Vector2 pos;
	int width;
	int height;
	bool active;
};

