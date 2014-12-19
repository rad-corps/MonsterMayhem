#pragma once

#include "ProgramState.h"

#include "Enums.h"

class OuterLoop
{
public:
	OuterLoop(void);
	~OuterLoop(void);

	//the main game loop, returns when it is time to shut down
	void Go();


private: 
	//The state machine variable
	ProgramState* currentProgramState;

	unsigned int cursorSprite;
	double mouseX; 
	double mouseY;
	
	//PROGRAM_STATES new
	bool shuttingDown;

};

