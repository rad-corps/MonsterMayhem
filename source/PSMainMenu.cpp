#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "AIE.h"
#include "Enums.h"


PSMainMenu::PSMainMenu(void)
{
	cout << "PSMainMenu()" << endl;
}


PSMainMenu::~PSMainMenu(void)
{
	cout << "~PSMainMenu()" << endl;
}


ProgramState* PSMainMenu::Update(float delta_)
{
	if ( IsKeyDown(KEY_ENTER) ) 
	{
		return new PSGameLoop();
	}
	return nullptr;
}

void PSMainMenu::Draw()
{
	DrawString( "Press Enter to start", 100, 100, 1.f, SColour(255,255,255,255));
}