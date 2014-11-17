#pragma once

#include "Vector.h"
#include "Rect.h"

class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);

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

