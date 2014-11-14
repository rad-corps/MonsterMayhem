#pragma once

#include "ProgramState.h"

class PSGameOver :
	public ProgramState
{
public:
	PSGameOver(void);
	~PSGameOver(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();
};

