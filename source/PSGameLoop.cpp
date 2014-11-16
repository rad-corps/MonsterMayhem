#include "PSGameLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "Enums.h"
#include "Collision.h"
#include "PSGameOver.h"
#include "WaveGen.h"


PSGameLoop::PSGameLoop(void)
{
	cout << "PSGameLoop()" << endl;

	player.RegisterSpitObserver(this);

	wave = 1;
	
	//SPIT_POOL is arbitrary at this stage. its the number in the pool of spit *shakes head at own pun*
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		spitList.push_back(Spit());
	}

	WaveItems waveItems = WaveGen::Generate(wave++, &player);
	monsterList = waveItems.monsterList;
	powerUpList = waveItems.powerUpList;
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

	//should we gen a new wave? 
	if ( !waveStillRunning)
	{
		WaveItems waveItems = WaveGen::Generate(wave++, &player);
		monsterList = waveItems.monsterList;
		powerUpList = waveItems.powerUpList;
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

	return nullptr;
}

void PSGameLoop::Draw()
{
	DrawString( "You are now playing the game, ESC to exit", 100, 100, 1.f, SColour(255,255,255,255));

	terrain.Draw();
	
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