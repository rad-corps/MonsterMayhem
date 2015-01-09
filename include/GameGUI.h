//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// GameGUI.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"
#include "GameObject.h"
#include "Enums.h"
#include "PlayerObserver.h"

class GameGUI : public GameObject, public PlayerObserver
{
public:
	GameGUI(void);
	~GameGUI(void);

	//must be called before draw
	void SetGameState(GAME_LOOP_STATE state_);
	

	virtual void Update(float delta_);
	virtual void Draw();
	virtual void UpdatePlayerGUI(float saliva_, float stamina_) ; 

	void SetEnemyLore(int slugs_, int moths_, int walkers_);

	void AddScore(int score_);
	int Score();

private:

	//sprites
	unsigned int sprBegWave;
	unsigned int sprEndWave;
	unsigned int sprDigit[10];

	unsigned int blueBar;
	unsigned int greenBar;
	unsigned int yellowBar;
	unsigned int barBG;
	unsigned int blackSprite;
	unsigned int walkerSprite;
	unsigned int mothSprite;
	unsigned int slugSprite;

	int numSlug;
	int numWalker;
	int numMoth;

	Vector2 staminaPos;
	Vector2 salivaPos;
	Vector2 scorePos;
		
	int staminaBars;
	int salivaBars;

	int score;

	Vector2 sprEndPos;
	Vector2 sprBegPos;

	GAME_LOOP_STATE state;

	float fps;
};

