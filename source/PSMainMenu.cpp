#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "AIE.h"
#include "Enums.h"
#include "FileSettings.h"


PSMainMenu::PSMainMenu(void)
{
	cout << "PSMainMenu()" << endl;
	sprite = CreateSprite("./images/Main_Menu.png", SCREEN_W, SCREEN_H, false);
	objectiveSprite = CreateSprite("./images/howto_objective.png", SCREEN_W, SCREEN_H, false);
	powerupSprite = CreateSprite("./images/howto_powerups.png", SCREEN_W, SCREEN_H, false);

	state = MAIN_MENU_STATE::MAIN_MENU_SCREEN;

	startButtonPos = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_X"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_Y"));
	startButtonSize = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_WIDTH"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_HEIGHT"));

	howToPlayButtonPos = Vector2(FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_X"), FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_Y"));
	howToPlayButtonSize = Vector2(FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_WIDTH"), FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_HEIGHT"));

	instructionsNextButtonPos = Vector2(FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_X"), FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_Y"));
	instructionsNextButtonSize = Vector2(FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_WIDTH"), FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_HEIGHT"));

	lastMouseState = false;

}


PSMainMenu::~PSMainMenu(void)
{
	cout << "~PSMainMenu()" << endl;
}


ProgramState* PSMainMenu::Update(float delta_)
{

	
	if ( lastMouseState && GetMouseButtonReleased(0) )
	{		
		double mouseX; 
		double mouseY;
		GetMouseLocation(mouseX, mouseY);
		cout << "MouseLoc - X: " << mouseX << "\tY: " << mouseY << endl;
		
		if ( state == MAIN_MENU_STATE::MAIN_MENU_SCREEN )
		{
			if ( mouseX >= startButtonPos.x && 
				mouseX <=  startButtonPos.x + startButtonSize.x &&
				mouseY >= startButtonPos.y &&
				mouseY <= startButtonPos.y + startButtonSize.y )
			{
				return new PSGameLoop();
			}

			if ( mouseX >= howToPlayButtonPos.x && 
				mouseX <=  howToPlayButtonPos.x + howToPlayButtonSize.x &&
				mouseY >= howToPlayButtonPos.y &&
				mouseY <= howToPlayButtonPos.y + howToPlayButtonSize.y )
			{
				state = MAIN_MENU_STATE::OBJECTIVE_SCREEN;
			}
		}

		if ( state == MAIN_MENU_STATE::OBJECTIVE_SCREEN || state == MAIN_MENU_STATE::POWERUP_SCREEN )
		{
			if ( mouseX >= instructionsNextButtonPos.x && 
				mouseX <=  instructionsNextButtonPos.x + instructionsNextButtonSize.x &&
				mouseY >= instructionsNextButtonPos.y &&
				mouseY <= instructionsNextButtonPos.y + instructionsNextButtonSize.y )
			{
				if ( state == MAIN_MENU_STATE::OBJECTIVE_SCREEN )
					state = MAIN_MENU_STATE::POWERUP_SCREEN;
				else if ( state == MAIN_MENU_STATE::POWERUP_SCREEN ) 
					state = MAIN_MENU_STATE::MAIN_MENU_SCREEN;
			}
		}


	}

	lastMouseState = GetMouseButtonDown(0);
	return nullptr;
}

void PSMainMenu::Draw()
{
	if ( state == MAIN_MENU_STATE::MAIN_MENU_SCREEN )
		currentSprite = sprite;		
	else if ( state == MAIN_MENU_STATE::OBJECTIVE_SCREEN )
		currentSprite = objectiveSprite;
	else if ( state == MAIN_MENU_STATE::POWERUP_SCREEN)
		currentSprite = powerupSprite;

	MoveSprite(currentSprite, 0.0f, SCREEN_H);
	DrawSprite(currentSprite);
}