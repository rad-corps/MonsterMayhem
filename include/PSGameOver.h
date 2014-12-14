#pragma once

#include "ProgramState.h"
#include "Vector.h"

class PSGameOver :
	public ProgramState
{
public:
	PSGameOver(void);
	~PSGameOver(void);

	void SetScore(int score_);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

private:
	int score;
	unsigned int sprite;
	Vector2 resetButtonPos;
	Vector2 resetButtonSize;
};

