#include "PSGameLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "Enums.h"
#include "Collision.h"
#include "PSGameOver.h"
#include "WaveGen.h"
#include "FileSettings.h"
#include "FrameworkHelpers.h"


PSGameLoop::PSGameLoop(void)
{
	cout << "PSGameLoop()" << endl;

	gameState = GAME_LOOP_STATE::WAVE_BEGIN;
	currentTimer = 0.0f;

	player.RegisterSpitObserver(this);

	wave = 1;
	
	//SPIT_POOL is arbitrary at this stage. its the number in the pool of spit *shakes head at own pun*
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		spitList.push_back(Spit());
	}

	waveBeginTimer = FileSettings::GetFloat("WAVE_BEGIN_TIMER");
	waveEndTimer = FileSettings::GetFloat("WAVE_END_TIMER");

	//LHS
	fences.push_back(Fence(Vector2(0, 0), FENCE_DIRECTION::FENCE_DIRECTION_UP, BORDER_FENCE_TILES));
	//RHS
	fences.push_back(Fence(Vector2(TERRAIN_W * (TERRAIN_COLS - 1), TERRAIN_H ), FENCE_DIRECTION::FENCE_DIRECTION_UP, BORDER_FENCE_TILES));
	//BOTTOM
	fences.push_back(Fence(Vector2(0, 0), FENCE_DIRECTION::FENCE_DIRECTION_RIGHT, BORDER_FENCE_TILES));
	//TOP
	fences.push_back(Fence(Vector2(0, TERRAIN_H * (TERRAIN_ROWS-1)), FENCE_DIRECTION::FENCE_DIRECTION_RIGHT, BORDER_FENCE_TILES));
	
	//add all the fences to the collision list
	for (int i = 0; i < fences.size(); ++i ) 
	{
		vector<Rect> temp =  fences[i].GetCollisionRects();
		fenceRects.insert(fenceRects.end(), temp.begin(), temp.end());
	}
}


PSGameLoop::~PSGameLoop(void)
{
	MoveCamera(0.0f, 0.0f);
	cout << "~PSGameLoop()" << endl;
}

ProgramState* PSGameLoop::Update(float delta_)
{
	//check if we want to switch states
	if ( IsKeyDown(KEY_ESCAPE) ) 
	{
		return new PSMainMenu();
	}

	currentTimer += delta_;

	//update the terrain (does nothing at this stage)
	terrain.Update(delta_);

	//update the player
	player.Update(delta_);

	//update the pool of loogies
	for (int i = 0; i < SPIT_POOL; ++i )
	{
		spitList[i].Update(delta_);
	}

	//check if all enemies have been killed
	bool waveStillRunning = false;

	//check for collision with fence and player
	for (int i = 0; i < fenceRects.size(); ++i )
	{
		if ( Collision::RectCollision(fenceRects[i], player.GetRect()) )
		{
			player.UndoUpdate();
		}
	}

	//update monsters
	for (int i = 0; i < monsterList.size(); ++i ) 
	{
		monsterList[i].Update(delta_);

		//is there at least one enemy still alive? 
		if ( monsterList[i].IsActive() )
			waveStillRunning = true;
		
		//check collision with player, game over if collided
		if ( Collision::CheckCollision(&monsterList[i], &player) )
		{
			cout << "GAME OVER" << endl;
			return new PSGameOver();
		}		

		//check this monster against each spit (BRUTE FORCE OH YEAH)
		for (int spit = 0; spit < spitList.size(); ++ spit )
		{
			if ( Collision::CheckCollision(&monsterList[i], &spitList[spit]))
			{
				monsterList[i].Hit();
				spitList[spit].SetActive(false);
			}
		}
	}

	//is this the end of the current wave?
	if ( gameState == GAME_LOOP_STATE::WAVE_RUNNING && !waveStillRunning) 
	{
		cout << "GAME_LOOP_STATE::WAVE_END" << endl;
		gameState = GAME_LOOP_STATE::WAVE_END;
		currentTimer = 0.0f;		
	}

	//wave begin has shown long enough, lets gen the wave.
	if ( gameState == GAME_LOOP_STATE::WAVE_BEGIN && currentTimer > waveBeginTimer) 
	{
		cout << "GAME_LOOP_STATE::WAVE_RUNNING" << endl;
		gameState = GAME_LOOP_STATE::WAVE_RUNNING;
		WaveItems waveItems = WaveGen::Generate(wave++, &player);
		monsterList = waveItems.monsterList;
		powerUpList = waveItems.powerUpList;
		currentTimer = 0.0f;		
	}

	//should we gen a new wave? 
	if ( gameState == GAME_LOOP_STATE::WAVE_END && currentTimer > waveEndTimer )
	{
		cout << "GAME_LOOP_STATE::WAVE_BEGIN" << endl;
		gameState = GAME_LOOP_STATE::WAVE_BEGIN;	
		currentTimer = 0.0f;
	}

	//update power ups
	for ( int i = 0; i < powerUpList.size(); ++i )
	{
		powerUpList[i].Update(delta_);
		
		if  (Collision::CheckCollision(&player, &powerUpList[i]))
		{
			player.EatPowerUp(powerUpList[i]);			
		}
	}

	//update gui
	gui.SetGameState(gameState);
	gui.Update(delta_);
	

	//environmental
	for (int i = 0; i < fences.size(); ++i )
	{
		fences[i].Update();
	}

	//return null (do not change current ProgramState)
	return nullptr;
}

void PSGameLoop::Draw()
{
	terrain.Draw();
	
	//draw fences
	for (int i = 0; i < fences.size(); ++i )
	{
		fences[i].Draw();
	}
	
	for ( int i = 0; i < powerUpList.size(); ++i )
	{
		powerUpList[i].Draw();
	}
	
	player.Draw();
	
	for (int i = 0; i < SPIT_POOL; ++i )
	{
		spitList[i].Draw();
	}

	for (int i = 0; i < monsterList.size(); ++i ) 
	{
		monsterList[i].Draw();
	}

	gui.Draw();
}

void PSGameLoop::SpitEvent(Vector2 position_, float rotation_, float activeTime_)
{
	//get a spit that isnt currently active
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		if ( !spitList[i].IsActive() )
		{
			spitList[i].HockOne(position_, rotation_, activeTime_);
			break;
		}
	}
}