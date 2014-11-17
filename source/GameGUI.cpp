#include "GameGUI.h"
#include "FileSettings.h"
#include "AIE.h"
#include "FrameworkHelpers.h"

GameGUI::GameGUI(void)
{
	//create the sprites
	sprBegWave = CreateSprite("./images/Wave_Begin.png", 
		FileSettings::GetInt("BEG_WAVE_WIDTH"),
		FileSettings::GetInt("BEG_WAVE_HEIGHT"),
		false);

	sprEndWave = CreateSprite("./images/Wave_Complete.png", 
		FileSettings::GetInt("COMPLETE_WAVE_WIDTH"),
		FileSettings::GetInt("COMPLETE_WAVE_HEIGHT"),
		false);

	for (int i = 0; i < 10; ++i )
	{
		string fileName = string("./images/") + std::to_string(i) + string(".png");
		sprDigit[i] = CreateSprite(fileName.c_str(), 
			FileSettings::GetInt("WAVE_DIGIT_WIDTH"),
			FileSettings::GetInt("WAVE_DIGIT_HEIGHT"),
			false);
	}

	sprBegPos = Vector2( FileSettings::GetFloat("BEG_WAVE_X"), FileSettings::GetFloat("BEG_WAVE_Y"));
	sprEndPos = Vector2( FileSettings::GetFloat("COMPLETE_WAVE_X"), FileSettings::GetFloat("COMPLETE_WAVE_Y"));
}


GameGUI::~GameGUI(void)
{
}

void GameGUI::SetGameState(GAME_LOOP_STATE state_)
{
	state = state_;
}

void GameGUI::Update(float delta_)
{
	//must use our own MoveSpriteAbs function because of the camera. 
	MoveSpriteAbs(sprBegWave, sprBegPos.x, sprBegPos.y - 200);
	MoveSpriteAbs(sprBegWave, sprBegPos.x, sprBegPos.y);
	MoveSpriteAbs(sprEndWave, sprEndPos.x, sprEndPos.y);
}

void GameGUI::Draw()
{
	if ( state == GAME_LOOP_STATE::WAVE_END )
	{
		DrawSprite(sprEndWave);
	}
	
	if ( state == GAME_LOOP_STATE::WAVE_BEGIN )
	{
		DrawSprite(sprBegWave);
	}
}
