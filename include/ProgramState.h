//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// ProgramState.h
/////////////////////////////////////////////////////////////////////////

#pragma once
class ProgramState
{
public:
	virtual ~ProgramState(){};
	virtual ProgramState* Update(float delta_) = 0;
	virtual void Draw() = 0;

	virtual bool ShuttingDown();

protected:
	bool shuttingDown;
};

