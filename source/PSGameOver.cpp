#include "PSGameOver.h"
#include "AIE.h"
#include "PSMainMenu.h"
#include "FileSettings.h"
#include "Enums.h"
#include "FrameworkHelpers.h"

PSGameOver::PSGameOver(void)
{
	sprite = CreateSprite("./images/Game_Over.png", SCREEN_W, SCREEN_H, false);
	resetButtonPos = Vector2(FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_X"), FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_Y"));
	resetButtonSize = Vector2(FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_WIDTH"), FileSettings::GetFloat("GAME_OVER_RESET_BUTTON_HEIGHT"));
}


PSGameOver::~PSGameOver(void)
{
}

void PSGameOver::SetScore(int score_)
{
	score = score_;
}


ProgramState* PSGameOver::Update(float delta_)
{
	MoveSprite(sprite, 0.0f, SCREEN_H);
	
	if (  GetMouseButtonDown(0) )
	{
		double mouseX; 
		double mouseY;
		GetMouseLocation(mouseX, mouseY);
		
		if ( mouseX >= resetButtonPos.x && 
			mouseX <=  resetButtonPos.x + resetButtonSize.x &&
			mouseY >= resetButtonPos.y &&
			mouseY <= resetButtonPos.y + resetButtonSize.y )
		{
			return new PSMainMenu();
		}
	}
	return nullptr;
}

void PSGameOver::Draw()
{
	DrawSprite(sprite);
	DrawStringAbs((string("FINAL SCORE  ") + to_string(score)).c_str(), (SCREEN_W/2) - 100 , (SCREEN_H/2)-100);
}