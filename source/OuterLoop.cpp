#include "OuterLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"

OuterLoop::OuterLoop(void)
{
	cout << "OuterLoop()" << endl;
	Initialise( SCREEN_W, SCREEN_H,  false, "Monster Mayhem" );

	SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
	AddFont( "./fonts/invaders.fnt" );
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
		}
		else//otherwise just draw the current one. 
		{
			currentProgramState->Draw();
		}
	
	}while ( FrameworkUpdate() == false );
}
