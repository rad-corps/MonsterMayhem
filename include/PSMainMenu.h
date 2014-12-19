#pragma once

#include "programstate.h"
#include "Vector.h"
#include "Enums.h"

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
	unsigned int objectiveSprite;
	unsigned int powerupSprite;

	unsigned int currentSprite;

	bool lastMouseState; //true for down, false for released

	MAIN_MENU_STATE state;

	Vector2 startButtonPos;
	Vector2 startButtonSize;

	Vector2 howToPlayButtonPos;
	Vector2 howToPlayButtonSize;

	Vector2 instructionsNextButtonPos;
	Vector2 instructionsNextButtonSize;

	Vector2 exitButtonPos;
	Vector2 exitButtonSize;
};

