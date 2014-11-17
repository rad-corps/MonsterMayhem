#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "AIE.h"
#include "Enums.h"
#include "FileSettings.h"


PSMainMenu::PSMainMenu(void)
{
	cout << "PSMainMenu()" << endl;
	sprite = CreateSprite("./images/Main_Menu.png", SCREEN_W, SCREEN_H, false);

	startButtonPos = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_X"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_Y"));
	startButtonSize = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_WIDTH"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_HEIGHT"));
}


PSMainMenu::~PSMainMenu(void)
{
	cout << "~PSMainMenu()" << endl;
}


ProgramState* PSMainMenu::Update(float delta_)
{
	MoveSprite(sprite, 0.0f, SCREEN_H);

	if ( GetMouseButtonDown(0) )
	{		
		double mouseX; 
		double mouseY;
		GetMouseLocation(mouseX, mouseY);
		cout << "MouseLoc - X: " << mouseX << "\tY: " << mouseY << endl;
		
		if ( mouseX >= startButtonPos.x && 
			mouseX <=  startButtonPos.x + startButtonSize.x &&
			mouseY >= startButtonPos.y &&
			mouseY <= startButtonPos.y + startButtonSize.y )
		{
			return new PSGameLoop();
		}
	}

	//if ( IsKeyDown(KEY_ENTER) ) 
	//{
	//	return new PSGameLoop();
	//}
	return nullptr;
}

void PSMainMenu::Draw()
{
	DrawSprite(sprite);
	//DrawString( "Press Enter to start", 100, 100, 1.f, SColour(255,255,255,255));
}