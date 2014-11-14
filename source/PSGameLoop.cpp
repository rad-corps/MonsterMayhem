#include "PSGameLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "Enums.h"


PSGameLoop::PSGameLoop(void)
{
	cout << "PSGameLoop()" << endl;

	player.RegisterSpitObserver(this);
	
	//SPIT_POOL is arbitrary at this stage. its the number in the pool of spit *shakes head at own pun*
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		spitList.push_back(Spit());
	}
	
	//create some random monsters
	for (int i = 0; i < 40; ++i )
	{
		Monster temp;
		temp.RegisterTarget(&player);
		monsterList.push_back(temp);
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

	//update the terrain (does nothing at this stage)
	terrain.Update(delta_);

	//update the player
	player.Update(delta_);

	//update the pool of loogies
	for (int i = 0; i < SPIT_POOL; ++i )
	{
		spitList[i].Update(delta_);
	}

	for (int i = 0; i < monsterList.size(); ++i ) 
	{
		monsterList[i].Update(delta_);
	}

	return nullptr;
}

void PSGameLoop::Draw()
{
	DrawString( "You are now playing the game, ESC to exit", 100, 100, 1.f, SColour(255,255,255,255));

	terrain.Draw();
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
	cout << "SPIT!!!" << endl;

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