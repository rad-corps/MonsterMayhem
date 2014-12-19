#include "OuterLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "windows.h"
#include "FrameworkHelpers.h"

OuterLoop::OuterLoop(void)
{
	cout << "OuterLoop()" << endl;
	Initialise( SCREEN_W, SCREEN_H,  false, "Monster Mayhem" );
	ShowCursor(FALSE);

	SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
	AddFont( "./fonts/invaders.fnt" );

	cursorSprite = CreateSprite("./images/circle_white.png", 32, 32, true);

	mouseX = 0.0;
	mouseY = 0.0;

	shuttingDown = false;
}


OuterLoop::~OuterLoop(void)
{
	cout << "~OuterLoop()" << endl;
}

void OuterLoop::Go()
{
	currentProgramState = new PSMainMenu();	
	do 
	{
		ClearScreen();

		//if state is going to change, Update will return the new state, otherwise it returns nullptr
		ProgramState* newState = currentProgramState->Update(GetDeltaTime());
		
		//change state
		if ( newState != nullptr )
		{
			delete currentProgramState;
			currentProgramState = newState;
			if ( currentProgramState->ShuttingDown() ) 
				break;
		}
		else//otherwise just draw the current one. 
		{
			currentProgramState->Draw();
			
			//draw mouse cursor
			GetMouseLocationEx(mouseX, mouseY, SCREEN_H);
			MoveSpriteAbs(cursorSprite, mouseX, mouseY);
			DrawSprite(cursorSprite);
		}
	
	}while ( FrameworkUpdate() == false );
}
