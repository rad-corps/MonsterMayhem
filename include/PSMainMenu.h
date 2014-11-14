#pragma once

#include "programstate.h"

class PSMainMenu :
	public ProgramState
{
public:
	PSMainMenu(void);
	virtual ~PSMainMenu(void);


	//implementations for ProgramState interface
	virtual ProgramState* Update(float delta_);
	virtual void Draw();
};

