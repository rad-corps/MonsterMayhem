#pragma once

#include "programstate.h"
#include "Vector.h"

class PSMainMenu :
	public ProgramState
{
public:
	PSMainMenu(void);
	virtual ~PSMainMenu(void);


	//implementations for ProgramState interface
	virtual ProgramState* Update(float delta_);
	virtual void Draw();

private: 
	unsigned int sprite;
	Vector2 startButtonPos;
	Vector2 startButtonSize;
};

