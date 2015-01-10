//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// GameGUI.cpp
/////////////////////////////////////////////////////////////////////////

#include "GameGUI.h"
#include "FileSettings.h"
#include "AIE.h"
#include "FrameworkHelpers.h"

GameGUI::GameGUI(void)
{
	blueBar = CreateSprite("./images/blue_bar.png", 36, 20, false);
	greenBar = CreateSprite("./images/green_bar.png", 36, 20, false);
	yellowBar;
	barBG;

	//create the sprites
	sprBegWave = CreateSprite("./images/Wave_Begin.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);
	sprEndWave = CreateSprite("./images/Wave_Complete.png", FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"), false);

	blackSprite =  CreateSprite("./images/black.png", 
		FileSettings::GetInt("SCREEN_W") + 2,
		FileSettings::GetInt("GUI_HEIGHT"),
		false);

	mothSprite =  CreateSprite("./images/moth.png", 64, 64,	true);
	slugSprite =  CreateSprite("./images/slug.png", 64, 64,	true);
	walkerSprite =  CreateSprite("./images/walker.png", 64, 64,	true);

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
	scorePos = Vector2(FileSettings::GetInt("SCORE_X"),FileSettings::GetInt("SCORE_Y"));

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
	
	//trying out the new range for loop
	for ( auto &text : textList ) 
	{
		text.Update(delta_);
	}
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

void GameGUI::AddScore(int score_, Vector2 pos_)
{
	score += score_;
	textList.push_back(TweenText(to_string(score_), pos_));
}

int GameGUI::Score()
{
	return score;
}

void GameGUI::Draw()
{
	for ( auto &text : textList ) 
	{
		text.Draw();
	}

	//draw GUI Bar first
	MoveSpriteAbs(blackSprite, -1, FileSettings::GetInt("GUI_HEIGHT"));
	DrawSprite(blackSprite);

	//display number of slugs
	MoveSpriteAbs(slugSprite, FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_SLUG_NUM_X"),  FileSettings::GetInt("GUI_SLUG_NUM_Y"));
	DrawSprite(slugSprite);
	DrawStringAbs(to_string(numSlug).c_str(), FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_SLUG_NUM_X") - 10, FileSettings::GetInt("GUI_SLUG_NUM_Y") - 40);

	//display number of moths
	MoveSpriteAbs(mothSprite, FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_MOTH_NUM_X"),  FileSettings::GetInt("GUI_MOTH_NUM_Y"));
	DrawSprite(mothSprite);
	DrawStringAbs(to_string(numMoth).c_str(), FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_MOTH_NUM_X") - 10, FileSettings::GetInt("GUI_MOTH_NUM_Y") - 40);

	//display number of walkers
	MoveSpriteAbs(walkerSprite, FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_WALKER_NUM_X"),  FileSettings::GetInt("GUI_WALKER_NUM_Y"));
	DrawSprite(walkerSprite);
	DrawStringAbs(to_string(numWalker).c_str(), FileSettings::GetInt("SCREEN_W") - FileSettings::GetInt("GUI_WALKER_NUM_X") - 10, FileSettings::GetInt("GUI_WALKER_NUM_Y") - 40);



	if ( state == GAME_LOOP_STATE::WAVE_END )
	{
		//MoveSpriteAbs(sprEndWave, sprEndPos.x * FileSettings::GetInt("SCREEN_W"), sprEndPos.y * FileSettings::GetInt("SCREEN_H"));
		MoveSpriteAbs(sprEndWave, 0.0f, FileSettings::GetInt("SCREEN_H"));
		DrawSprite(sprEndWave);
	}
	
	if ( state == GAME_LOOP_STATE::WAVE_BEGIN )
	{
		//MoveSpriteAbs(sprBegWave, sprBegPos.x * FileSettings::GetInt("SCREEN_W"), sprBegPos.y * FileSettings::GetInt("SCREEN_H"));
		MoveSpriteAbs(sprBegWave, 0.0f, FileSettings::GetInt("SCREEN_H"));
		DrawSprite(sprBegWave);
		//DrawStringAbs((string("Slugs:   ") + to_string(numSlug  )).c_str(), 100, 300);
		//DrawStringAbs((string("Moths:   ") + to_string(numMoth  )).c_str(), 100, 400);
		//DrawStringAbs((string("Walkers: ") + to_string(numWalker)).c_str(), 100, 500);
	}

	if ( FileSettings::GetBool("SHOW_FPS") ) 
	{
		DrawStringAbs(to_string(fps).c_str(), 50,50);
	}

	//draw score
	DrawStringAbs("SCORE", FileSettings::GetInt("SCORE_X") ,FileSettings::GetInt("SCORE_Y") + 8);
	DrawStringAbs(to_string(score).c_str(), FileSettings::GetInt("SCORE_X") + FileSettings::GetInt("GUI_L_SPACE") ,FileSettings::GetInt("SCORE_Y") + 8);

	//draw stamina bars
	DrawStringAbs("STAMINA",  staminaPos.x, staminaPos.y + 8);
	for ( int i = 0; i < staminaBars; ++i )
	{
		//find position
		float posx = staminaPos.x + FileSettings::GetInt("GUI_L_SPACE") + (i * (FileSettings::GetInt("BAR_W") + (FileSettings::GetInt("BAR_H_MARGIN"))));
		MoveSpriteAbs(blueBar, posx, staminaPos.y);
		DrawSprite(blueBar);
	}

	//draw saliva bars
	DrawStringAbs("SALIVOMETER",  salivaPos.x, salivaPos.y + 8);
	for ( int i = 0; i < salivaBars; ++i )
	{
		//find position
		
		float posx = salivaPos.x + FileSettings::GetInt("GUI_L_SPACE") + (i * (FileSettings::GetInt("BAR_W") + (FileSettings::GetInt("BAR_H_MARGIN"))));
		MoveSpriteAbs(greenBar, posx, salivaPos.y);
		DrawSprite(greenBar);
	}
}
