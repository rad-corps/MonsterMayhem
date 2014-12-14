#include "PSGameLoop.h"
#include "PSMainMenu.h"
#include "AIE.h"
#include "Enums.h"
#include "Collision.h"
#include "PSGameOver.h"
#include "WaveGen.h"
#include "FileSettings.h"
#include "FrameworkHelpers.h"
#include "Node.h"
#include "PathFinder.h"


PSGameLoop::PSGameLoop(void)
{
	cout << "PSGameLoop()" << endl;

	gameState = GAME_LOOP_STATE::WAVE_BEGIN;
	currentTimer = 0.0f;
	paused = false;

	player.RegisterSpitObserver(this);
	player.RegisterPlayerObserver(&gui);
	Monster::RegisterExplosionObserver(this);

	wave = 1;
	
	//SPIT_POOL is arbitrary at this stage. its the number in the pool of spit *shakes head at own pun*
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		spitList.push_back(Spit());
	}

	waveBeginTimer = FileSettings::GetFloat("WAVE_BEGIN_TIMER");
	waveEndTimer = FileSettings::GetFloat("WAVE_END_TIMER");

	//create rivers
	terrain.SetRiverTile(5,15, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(5,14, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(6,14, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(7,14, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(7,13, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(7,12, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(7,11, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(8,11, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(9,11, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(9,10, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	
	//BRIDGE
	
	terrain.SetRiverTile(9,8,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(9,7,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(9,6,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(10,6, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(10,5, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(10,4, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(10,3, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(9,3,  FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	terrain.SetRiverTile(8,3,  FOUR_WAY_ROTATION::ROT_270, RIVER_TILE_TYPE::CORNER);
	terrain.SetRiverTile(8,2,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);

	//BRIDGE
	terrain.SetRiverTile(8,0,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);

	//top and bottom boundaries
	for (int i = 0; i < TERRAIN_COLS; ++i )
	{
		terrain.SetTreeTile(i,0);
		terrain.SetTreeTile(i,TERRAIN_ROWS-1);
	}

	//left and right boundaries
	for (int i = 0; i < TERRAIN_ROWS; ++i )
	{
		terrain.SetTreeTile(0,i);
		terrain.SetTreeTile(TERRAIN_COLS-1,i);
	}
}


PSGameLoop::~PSGameLoop(void)
{
	MoveCamera(0.0f, 0.0f);
	cout << "~PSGameLoop()" << endl;
}

void PSGameLoop::CleanMonsterList()
{
	for (int i = 0; i < monsterList.size(); ++i )
	{
		delete monsterList[i];
	}
	monsterList.clear();
}

void PSGameLoop::CheckPlayerTerrainCollision()
{
	//check for collision with fence and player
	for (int i = 0; i < fenceRects.size(); ++i )
	{
		if ( Collision::RectCollision(fenceRects[i], player.GetRect()) )
		{
			player.UndoUpdate();
		}
	}

	//check for collision with terrain and player
	vector<Rect> unwalkableTerrain = terrain.GetUnwalkableTerrain();
	for (int i = 0; i < unwalkableTerrain.size(); ++i )
	{
		if ( Collision::RectCollision(unwalkableTerrain[i], player.GetRect()) )
		{
			player.UndoUpdate();
		}
	}
}

ProgramState* PSGameLoop::Update(float delta_)
{
	//check if we want to switch states
	if ( IsKeyDown(KEY_ESCAPE) ) 
	{
		return new PSMainMenu();
	}

	if ( IsKeyDown (KEY_P))
	{
		paused = true;
	}

	if ( IsKeyDown(KEY_SPACE ))
	{
		paused = false;
	}

	if ( paused ) 
	{
		return nullptr;
	}

	currentTimer += delta_;

	//update the terrain (does nothing at this stage)
	terrain.Update(delta_);

	//update the player
	player.Update(delta_);
	player.UpdateXMovement(delta_);
	CheckPlayerTerrainCollision();
	player.UpdateYMovement(delta_);
	CheckPlayerTerrainCollision();

	//update the explosions
	for (int i = 0; i < explosions.size(); ++i )
	{
		explosions[i].Update(delta_);
	}

	//update the hit animations
	for (int i = 0; i < hitAnimations.size(); ++i )
	{
		hitAnimations[i].Update(delta_);
	}

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
		monsterList[i]->Update(delta_);

		//is there at least one enemy still alive? 
		if ( monsterList[i]->IsActive() )
			waveStillRunning = true;
		
		//check collision with player, game over if collided
		if ( Collision::CheckCollision(monsterList[i], &player) )
		{
			cout << "GAME OVER" << endl;
			cout << "Final Score: " << gui.Score();
			PSGameOver* state = new PSGameOver();
			state->SetScore(gui.Score());
			return state;
		}	

		//check collision between fence and monster			
		for (int fence = 0; fence < fenceRects.size(); ++fence )
		{
			if ( Collision::RectCollision(fenceRects[fence], monsterList[i]->GetRect()) )
			{
				monsterList[i]->HandleTerrainCollision();
			}
		}

		//check for collision with terrain and monster
		vector<Rect> unwalkableTerrain = terrain.GetUnwalkableTerrain();
		for (int terrain = 0; terrain < unwalkableTerrain.size(); ++terrain )
		{
			if ( Collision::RectCollision(unwalkableTerrain[terrain], monsterList[i]->GetRect()) )
			{
				monsterList[i]->HandleTerrainCollision();
			}
		}

		//check this monster against each spit (BRUTE FORCE OH YEAH)
		for (int spit = 0; spit < spitList.size(); ++ spit )
		{
			if ( Collision::CheckCollision(monsterList[i], &spitList[spit]))
			{
				//TODO add hit animation
				monsterList[i]->Hit();
				hitAnimations.push_back(HitAnimation(spitList[spit].Pos()));
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
		CleanMonsterList();
		WaveItems waveItems = WaveGen::Generate(wave++, &player, terrain.GetUnwalkableTerrain());
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

	//return null (do not change current ProgramState)
	return nullptr;
}

void PSGameLoop::Draw()
{
	terrain.Draw();

	////draw fences
	//for (int i = 0; i < fences.size(); ++i )
	//{
	//	fences[i].Draw();
	//}
	
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
		monsterList[i]->Draw();
	}

	for (int i = 0; i < explosions.size(); ++i ) 
	{
		explosions[i].Draw();
	}

	for (int i = 0; i < hitAnimations.size(); ++i ) 
	{
		hitAnimations[i].Draw();
	}

	//safeZone.Draw();

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

void PSGameLoop::ExplosionEvent(Vector2 position_, Vector2 direction_, int score_)
{
	explosions.push_back(Explosion(position_, direction_));
	gui.AddScore(score_);
}
