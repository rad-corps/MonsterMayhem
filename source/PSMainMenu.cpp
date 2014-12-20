#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSShuttingDown.h"
#include "AIE.h"
#include "Enums.h"
#include "FileSettings.h"



PSMainMenu::PSMainMenu(void)
{
	cout << "PSMainMenu()" << endl;
	sprite = CreateSprite("./images/Main_Menu.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);
	objectiveSprite = CreateSprite("./images/howto_objective.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);
	powerupSprite = CreateSprite("./images/howto_powerups.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);

	state = MAIN_MENU_STATE::MAIN_MENU_SCREEN;

	startButtonPos = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_X"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_Y"));
	startButtonSize = Vector2(FileSettings::GetFloat("MAIN_MENU_START_BUTTON_WIDTH"), FileSettings::GetFloat("MAIN_MENU_START_BUTTON_HEIGHT"));

	howToPlayButtonPos = Vector2(FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_X"), FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_Y"));
	howToPlayButtonSize = Vector2(FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_WIDTH"), FileSettings::GetFloat("HOW_TO_PLAY_BUTTON_HEIGHT"));

	instructionsNextButtonPos = Vector2(FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_X"), FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_Y"));
	instructionsNextButtonSize = Vector2(FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_WIDTH"), FileSettings::GetFloat("INSTRUCTIONS_NEXT_BUTTON_HEIGHT"));

	exitButtonPos = Vector2(FileSettings::GetFloat("EXIT_GAME_BUTTON_X"), FileSettings::GetFloat("EXIT_GAME_BUTTON_Y"));
	exitButtonSize = Vector2(FileSettings::GetFloat("EXIT_GAME_BUTTON_WIDTH"), FileSettings::GetFloat("EXIT_GAME_BUTTON_HEIGHT"));

	lastMouseState = false;

	shuttingDown = false;

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
		float percX = mouseX / FileSettings::GetInt("SCREEN_W");
		float percY = mouseY / FileSettings::GetInt("SCREEN_H");
		
		cout << "MouseLoc - X: " << mouseX << "\tY: " << mouseY << endl;
		cout << "Percentage - X: " << percX << "\tY: " << percY << endl;
		
		if ( state == MAIN_MENU_STATE::MAIN_MENU_SCREEN )
		{
			if ( percX >= startButtonPos.x && 
				percX <=  startButtonPos.x + startButtonSize.x &&
				percY >= startButtonPos.y &&
				percY <= startButtonPos.y + startButtonSize.y )
			{
				return new PSGameLoop();
			}

			if ( percX >= howToPlayButtonPos.x && 
				percX <=  howToPlayButtonPos.x + howToPlayButtonSize.x &&
				percY >= howToPlayButtonPos.y &&
				percY <= howToPlayButtonPos.y + howToPlayButtonSize.y )
			{
				state = MAIN_MENU_STATE::OBJECTIVE_SCREEN;
			}

			if ( percX >= exitButtonPos.x && 
				percX <=  exitButtonPos.x + exitButtonSize.x &&
				percY >= exitButtonPos.y &&
				percY <= exitButtonPos.y + exitButtonSize.y )
			{
				state = MAIN_MENU_STATE::SHUTTING_DOWN;
				return new PSShuttingDown();
			}
		}

		if ( state == MAIN_MENU_STATE::OBJECTIVE_SCREEN || state == MAIN_MENU_STATE::POWERUP_SCREEN )
		{
			if ( percX >= instructionsNextButtonPos.x && 
				percX <=  instructionsNextButtonPos.x + instructionsNextButtonSize.x &&
				percY >= instructionsNextButtonPos.y &&
				percY <= instructionsNextButtonPos.y + instructionsNextButtonSize.y )
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

	MoveSprite(currentSprite, 0.0f, FileSettings::GetInt("SCREEN_H"));
	DrawSprite(currentSprite);
}