//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PSGameOver.cpp
/////////////////////////////////////////////////////////////////////////

#include "PSGameOver.h"
#include "AIE.h"
#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "FileSettings.h"
#include "Enums.h"
#include "FrameworkHelpers.h"
#include "Sound.h"

PSGameOver::PSGameOver(void)
{
	sprite = CreateSprite("./images/Game_Over.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);
	resetButtonPos = Vector2(FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_X"), FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_Y"));
	resetButtonSize = Vector2(FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_WIDTH"), FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_HEIGHT"));
	continueButtonPos = Vector2(FileSettings::GetFloat("GAME_OVER_CONTINUE_BUTTON_X"), FileSettings::GetFloat("GAME_OVER_CONTINUE_BUTTON_Y"));
	continueButtonSize = Vector2(FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_WIDTH"), FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_HEIGHT"));
	shuttingDown = false;

	lastMouseState = false;
	Sound::PlayGameSound(SOUNDS::RESTART_SCREEN_MUSIC);
}


PSGameOver::~PSGameOver(void)
{
	Sound::StopSound(SOUNDS::RESTART_SCREEN_MUSIC);
}

void PSGameOver::SetScore(int score_, int level_)
{
	score = score_;
	level = level_;
}


ProgramState* PSGameOver::Update(float delta_)
{
	MoveSprite(sprite, 0.0f, FileSettings::GetInt("SCREEN_H"));
	
	if (  lastMouseState && GetMouseButtonReleased(0) )
	{
		double mouseX; 
		double mouseY;
		GetMouseLocation(mouseX, mouseY);
		float percX = mouseX / FileSettings::GetInt("SCREEN_W");
		float percY = mouseY / FileSettings::GetInt("SCREEN_H");
		
		cout << "MouseLoc - X: " << mouseX << "\tY: " << mouseY << endl;
		cout << "Percentage - X: " << percX << "\tY: " << percY << endl;
		
		if ( percX >= resetButtonPos.x && 
			percX <=  resetButtonPos.x + resetButtonSize.x &&
			percY >= resetButtonPos.y &&
			percY <= resetButtonPos.y + resetButtonSize.y )
		{
			
			return new PSMainMenu();
		}

		if ( percX >= continueButtonPos.x && 
			percX <=  continueButtonPos.x + continueButtonSize.x &&
			percY >= continueButtonPos.y &&
			percY <= continueButtonPos.y + continueButtonSize.y )
		{
			return new PSGameLoop(--level);
		}

	}

	lastMouseState = GetMouseButtonDown(0);

	return nullptr;
}

void PSGameOver::Draw()
{
	DrawSprite(sprite);
	DrawStringAbs((string("F I N A L   S C O R E    ") + to_string(score)).c_str(), (FileSettings::GetInt("SCREEN_W")/2) - 130 , (FileSettings::GetInt("SCREEN_H")/2)-100);
}