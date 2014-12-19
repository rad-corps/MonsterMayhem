#pragma once

#include "ProgramState.h"
#include "Player.h"
#include "Terrain.h"
#include "SpitObserver.h"
#include "Spit.h"
#include "MonsterSlug.h"
#include "PowerUp.h"
#include "GameGUI.h"
#include "Fence.h"
#include "SafeZone.h"
#include "ExplosionObserver.h"
#include "Explosion.h"
#include "HitAnimation.h"
#include <memory>

class PSGameLoop :
	public ProgramState, public SpitObserver, public ExplosionObserver
{
public:
	PSGameLoop(void);
	virtual ~PSGameLoop(void);

	//implementations for ProgramState interface
	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	//implementation of SpitObserver interface
	virtual void SpitEvent(Vector2 position_, float rotation_, float activeTime_); 
	
	//implementation of ExplosionObserver interface
	virtual void ExplosionEvent(Vector2 position_, Vector2 direction_, int score_); 

private:
	void CleanMonsterList();
	void CheckPlayerTerrainCollision();
	void BeginWave();

	//game objects
	Player player;
	Terrain terrain;
	vector<Spit> spitList;
	vector<Monster*> monsterList;
	vector<PowerUp> powerUpList;
	//vector<Rect> fenceRects;
	//vector<Fence> fences;
	vector<Explosion> explosions;
	vector<HitAnimation> hitAnimations;
	SafeZone safeZone;
	GameGUI gui;
	
	
	//keep track of current wave number
	int wave;

	//timers
	float waveBeginTimer;
	float waveEndTimer;
	float currentTimer;

	bool paused;

	//state
	GAME_LOOP_STATE gameState;

	
};

