#pragma once
class ProgramState
{
public:
	virtual ~ProgramState(){};
	virtual ProgramState* Update(float delta_) = 0;
	virtual void Draw() = 0;	
};

