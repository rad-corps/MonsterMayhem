#include "OuterLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "windows.h"
#include "FrameworkHelpers.h"
#include "wtypes.h"
#include "FileSettings.h"

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

OuterLoop::OuterLoop(void)
{
	//set the screen resolution variables in the filesettings map
	int hor, ver;
	GetDesktopResolution(hor, ver);
	cout << "Screen Res: " << hor << "x" << ver << endl;
	FileSettings::AddIntValue("SCREEN_W", hor);
	FileSettings::AddIntValue("SCREEN_H", ver);

	cout << "OuterLoop()" << endl;
	Initialise( FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"),  FileSettings::GetBool("FULL_SCREEN"), "Monster Mayhem" );
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
			GetMouseLocationEx(mouseX, mouseY, FileSettings::GetInt("SCREEN_H"));
			MoveSpriteAbs(cursorSprite, mouseX, mouseY);
			DrawSprite(cursorSprite);
		}
	
	}while ( FrameworkUpdate() == false );
}
