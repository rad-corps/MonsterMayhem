//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PSGameOver.h
/////////////////////////////////////////////////////////////////////////

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

	bool lastMouseState;
};

