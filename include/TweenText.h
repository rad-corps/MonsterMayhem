#pragma once

#include "GameObject.h"
#include "AIE.h"
#include <string>
#include "Vector.h"

class TweenText : public GameObject
{
public:
	TweenText(string text_, Vector2 startPos_, float maxTime_ = 1.3);
	~TweenText(void);

	virtual void Update(float delta_);
	virtual void Draw();

private:
	string text;
	float textSize;
	Vector2 textPos;
	//Vector2 targetPos;
	Vector2 velocity;
	float timer;
	float maxTime;
};

