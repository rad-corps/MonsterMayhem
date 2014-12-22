//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PSShuttingDown.h
/////////////////////////////////////////////////////////////////////////

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

