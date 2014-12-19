#pragma once
#include "ProgramState.h"

class PSShuttingDown : public ProgramState
{
public:
	PSShuttingDown(void);
	virtual ~PSShuttingDown(void);

	//implementations for ProgramState interface
	virtual ProgramState* Update(float delta_);
	virtual void Draw();
};

