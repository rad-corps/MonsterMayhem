#pragma once

#include "GameObject.h"
#include "AIE.h"
#include <string>
#include "Vector.h"

class TweenText : public GameObject
{
public:
	TweenText(int score_, Vector2 startPos_, float maxTime_ = 1.3);
	~TweenText(void);

	virtual void Update(float delta_);
	virtual void Draw();

private:
	int score;
	float textSize;
	//float maxTextSize;
	Vector2 textPos;
	//Vector2 targetPos;
	Vector2 velocity;
	float timer;
	float maxTime;
};

bool IsTextInactive(const TweenText& text_);

