#include "GameGUI.h"
#include "FileSettings.h"
#include "AIE.h"
#include "FrameworkHelpers.h"

GameGUI::GameGUI(void)
{
	blueBar = CreateSprite("./images/blue_bar.png", 36, 20, false);
	greenBar = CreateSprite("./images/green_bar.png", 36, 20, false);;
	yellowBar;
	barBG;

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
	staminaPos = Vector2(FileSettings::GetInt("STAMINA_X"),FileSettings::GetInt("STAMINA_Y"));
	salivaPos = Vector2(FileSettings::GetInt("SALIVA_X"),FileSettings::GetInt("SALIVA_Y"));

	score = 0;
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
	fps = 1 / delta_;
}

//saliva and stamina between 0 and 1
void GameGUI::UpdatePlayerGUI(float saliva_, float stamina_)
{
	//Yes I am a maths newb!!!!
	if ( stamina_ > 0.8f ) 
		staminaBars = 5;
	else if ( stamina_ > 0.6f ) 
		staminaBars = 4;
	else if ( stamina_ > 0.4f ) 
		staminaBars = 3;
	else if ( stamina_ > 0.2f ) 
		staminaBars = 2;
	else if ( stamina_ > 0.0f ) 
		staminaBars = 1;

	if ( saliva_ > 0.8f ) 
		salivaBars = 5;
	else if ( saliva_ > 0.6f ) 
		salivaBars = 4;
	else if ( saliva_ > 0.4f ) 
		salivaBars = 3;
	else if ( saliva_ > 0.2f ) 
		salivaBars = 2;
	else if ( saliva_ > 0.0f ) 
		salivaBars = 1;

	//staminaBars = stamina_ * 5;
	//salivaBars = saliva_ * 5;
}

void GameGUI::SetEnemyLore(int slugs_, int moths_, int walkers_)
{
	numSlug = slugs_;
	numMoth = moths_;
	numWalker = walkers_;
}

void GameGUI::AddScore(int score_)
{
	score += score_;
}



int GameGUI::Score()
{
	return score;
}

void GameGUI::Draw()
{
	if ( state == GAME_LOOP_STATE::WAVE_END )
	{
		MoveSpriteAbs(sprEndWave, sprEndPos.x, sprEndPos.y);
		DrawSprite(sprEndWave);
	}
	
	if ( state == GAME_LOOP_STATE::WAVE_BEGIN )
	{
		MoveSpriteAbs(sprBegWave, sprBegPos.x, sprBegPos.y);
		DrawSprite(sprBegWave);
		//DrawStringAbs((string("Slugs:   ") + to_string(numSlug  )).c_str(), 100, 300);
		//DrawStringAbs((string("Moths:   ") + to_string(numMoth  )).c_str(), 100, 400);
		//DrawStringAbs((string("Walkers: ") + to_string(numWalker)).c_str(), 100, 500);
	}

	DrawStringAbs(to_string(fps).c_str(), 50,50);
	DrawStringAbs((string("Score: ") + to_string(score)).c_str(), 50 ,SCREEN_H - 50);

	//draw stamina bars
	for ( int i = 0; i < staminaBars; ++i )
	{
		//find position
		float posx = staminaPos.x + (i * (FileSettings::GetInt("BAR_W") + (FileSettings::GetInt("BAR_H_MARGIN"))));
		MoveSpriteAbs(blueBar, posx, staminaPos.y);
		DrawSprite(blueBar);
	}

	//draw saliva bars
	for ( int i = 0; i < salivaBars; ++i )
	{
		//find position
		float posx = salivaPos.x + (i * (FileSettings::GetInt("BAR_W") + (FileSettings::GetInt("BAR_H_MARGIN"))));
		MoveSpriteAbs(greenBar, posx, salivaPos.y);
		DrawSprite(greenBar);
	}
}
