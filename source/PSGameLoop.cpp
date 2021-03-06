//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// PSGameLoop.cpp
/////////////////////////////////////////////////////////////////////////

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
#include "Sound.h"

void PSGameLoop::NextLevel()
{
	string fileName = "levels\\";
	fileName += "lvl";
	fileName += to_string(++level);
	fileName += ".csv";

	terrain.Load(fileName);

	//clear all enemies
	CleanMonsterList();
	
	player.SetPlayerPos(FileSettings::GetInt("PLAYER_X_TILE"), FileSettings::GetInt("PLAYER_Y_TILE"));

	//spawn the power ups for the player each time they finish a wave
	PowerUp p1;
	PowerUp p2;

	//trust the collision engine in update? 
	p1.Spawn(POWER_UP_TYPE::SPEED_UP, player.Pos());
	p2.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY, player.Pos());

	//implicitly eat it just in case
	player.EatPowerUp(p1);
	player.EatPowerUp(p2);
}

PSGameLoop::PSGameLoop(int level_)
{
	level = level_;
	cout << "PSGameLoop(" << level << ")" << endl;
	currentTimer = 0.0f;
	paused = false;
	
	player.RegisterSpitObserver(this);
	player.RegisterPlayerObserver(&gui);
	Monster::RegisterExplosionObserver(this);

	//wave = 1;
	
	//SPIT_POOL is arbitrary at this stage. its the number in the pool of spit *shakes head at own pun*
	for ( int i = 0; i < SPIT_POOL; ++i )
	{
		spitList.push_back(Spit());
	}

	waveBeginTimer = FileSettings::GetFloat("WAVE_BEGIN_TIMER");
	waveEndTimer = FileSettings::GetFloat("WAVE_END_TIMER");

	

	////create rivers
	//terrain.SetRiverTile(5,15, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(5,14, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(6,14, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(7,14, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(7,13, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(7,12, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(7,11, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(8,11, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(9,11, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(9,10, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//
	//
	//terrain.SetRiverTile(9,8,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(9,7,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(9,6,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(10,6, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(10,5, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(10,4, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(10,3, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(9,3,  FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
	//terrain.SetRiverTile(8,3,  FOUR_WAY_ROTATION::ROT_270, RIVER_TILE_TYPE::CORNER);
	//terrain.SetRiverTile(8,2,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);

	////BRIDGE
	//terrain.SetRiverTile(8,0,  FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);

	////top and bottom boundaries
	//for (int i = 0; i < TERRAIN_COLS; ++i )
	//{
	//	terrain.SetTreeTile(i,0);
	//	terrain.SetTreeTile(i,TERRAIN_ROWS-1);
	//}

	////left and right boundaries
	//for (int i = 0; i < TERRAIN_ROWS; ++i )
	//{
	//	terrain.SetTreeTile(0,i);
	//	terrain.SetTreeTile(TERRAIN_COLS-1,i);
	//}

	BeginWave();

	shuttingDown = false;

	showMenuTimer = 0.0f;
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

void PSGameLoop::CheckPlayerRiverCollision()
{
	//check for collision with river and player
	player.SetInRiver(false);

	vector<Rect> RiverTerrain = terrain.GetRiverTerrain();
	for (int i = 0; i < RiverTerrain.size(); ++i )
	{
		if ( Collision::RectCollision(RiverTerrain[i], player.GetRect(), 1.0f))
		{
		  player.SetInRiver(true);
          PowerUp temp;
          temp.Spawn(POWER_UP_TYPE::SPIT_FREQUENCY, Vector2());
		  player.EatPowerUp(temp); 

		}
	}
}

void PSGameLoop::CheckPlayerMudCollision()
{
	//check for collision with mud and player
	player.SetInMud(false);
	
	vector<Rect> mudTerrain = terrain.GetMudTerrain();
	for (int i = 0; i < mudTerrain.size(); ++i )
	{
		if ( Collision::RectCollision(mudTerrain[i], player.GetRect()) )
		{
			player.SetInMud(true);
		}
	}
}

void PSGameLoop::CheckPlayerGoalCollision()
{
	Rect goal = terrain.GetGoalTile();

	if ( Collision::RectCollision(goal, player.GetRect()) && monsterList.size() > 0 )
	{
		//Sound::PlayGameSound(SOUNDS::WIN_LEVEL);
		cout << "Level Complete - Load Next Level" << endl;
		CleanMonsterList();
		gameState = GAME_LOOP_STATE::GOAL_REACHED;
		gui.AddScore(100 * level, player.Pos());
	}
}

void PSGameLoop::BeginWave()
{
	NextLevel();
	gameState = GAME_LOOP_STATE::WAVE_BEGIN;	
	cout << "GAME_LOOP_STATE::WAVE_BEGIN" << endl;

	Sound::PlayGameSound(SOUNDS::GAME_MUSIC);

	CleanMonsterList();
	WaveItems waveItems = WaveGen::Generate(level, &player, terrain.GetUnwalkableTerrain());
	monsterList = waveItems.monsterList;
	powerUpList = waveItems.powerUpList;	
	currentTimer = 0.0f;

	gui.SetEnemyLore(waveItems.slugCount, waveItems.mothCount, waveItems.walkerCount);
}

ProgramState* PSGameLoop::Update(float delta_)
{
	////check if we want to switch states
	//if ( IsKeyDown(KEY_ESCAPE) ) 
	//{
	//	return new PSMainMenu();
	//}

	if ( !player.Alive() && player.DeathAnimationFinished() ) 
	{

		showMenuTimer += delta_;

		if ( showMenuTimer > FileSettings::GetFloat("TIME_TO_WAIT_AFTER_DEATH") ) 
		{
			PSGameOver* state = new PSGameOver();
			state->SetScore(gui.Score(), level);
			return state;
		}
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

		//check against the treelist
		vector<Rect> unspittable = terrain.GetUnspittableTerrain();

		for (int terrain = 0; terrain < unspittable.size(); ++terrain )
		{
			if ( spitList[i].IsActive() ) 
			{
				if ( Collision::RectCollision(unspittable[terrain], spitList[i].GetRect()) )
				{
					spitList[i].SetActive(false);
					Sound::PlayGameSound(SOUNDS::TREE_HIT);				
				}
			}
		}
	}

	//check if all enemies have been killed
	//bool waveStillRunning = false;

	//update player regardless of whether the wave has started
	player.Update(delta_);

	if ( gameState != GAME_LOOP_STATE::WAVE_BEGIN )
	{
		//Capture player input and check for collission

		CheckPlayerRiverCollision();
		player.UpdateYMovement(delta_);
		CheckPlayerTerrainCollision();
		player.UpdateXMovement(delta_);
		CheckPlayerTerrainCollision();
		CheckPlayerMudCollision();
		
		//CheckPlayerTerrainCollision();
		CheckPlayerGoalCollision();

		int slugNum = 0;
		int mothNum = 0;
		int walkerNum = 0;

		//update monsters
		for (int i = 0; i < monsterList.size(); ++i ) 
		{
			//increment monster counters
			if ( monsterList[i]->IsActive() )
			{
				if ( monsterList[i]->Type() == MONSTER_TYPE::FAT_WALKER  ) ++walkerNum;
				if ( monsterList[i]->Type() == MONSTER_TYPE::MOTH ) ++mothNum;
				if ( monsterList[i]->Type() == MONSTER_TYPE::SLUG) ++slugNum;
			}

			//is there at least one enemy still alive? 
			//if ( monsterList[i]->IsActive() )
			//	waveStillRunning = true;
		
			//check collision with player, game over if collided
			if ( player.Alive() && Collision::CheckCollision(monsterList[i], &player) )
			{
				Sound::PlayGameSound(SOUNDS::PLAYER_DEATH);
				Sound::PlayGameSound(SOUNDS::GAME_OVER_MUSIC);
				Sound::StopSound(SOUNDS::GAME_MUSIC);
				cout << "GAME OVER" << endl;
				cout << "Final Score: " << gui.Score();
				gameState = GAME_LOOP_STATE::PLAYER_DIED;
				player.Die();
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

			//reset enemy in mud status
			for (int j = 0; j < monsterList.size(); ++j )
			{
				monsterList[j]->SetInMud(false);
			}

			//check for collision with mud and monster
			vector<Rect> mudTerrain = terrain.GetMudTerrain();
			for (int terrain = 0; terrain < mudTerrain.size(); ++terrain )
			{
				if ( Collision::RectCollision(mudTerrain[terrain], monsterList[i]->GetRect()) )
				{					
					monsterList[i]->SetInMud(true);
				}
			}

			//check this monster against each spit (BRUTE FORCE OH YEAH)
			for (int spit = 0; spit < spitList.size(); ++ spit )
			{
				if ( Collision::CheckCollision(monsterList[i], &spitList[spit]))
				{
					//TODO add hit animation
					monsterList[i]->Hit();
					gui.AddScore(10, (*monsterList[i]).Pos());
					hitAnimations.push_back(HitAnimation(spitList[spit].Pos()));
					spitList[spit].SetActive(false);
				}
			}

			monsterList[i]->Update(delta_);
		}
		gui.SetEnemyLore(slugNum, mothNum, walkerNum);
	}

	//is this the end of the current wave?
	//if ( gameState == GAME_LOOP_STATE::WAVE_RUNNING && !waveStillRunning) 
	if ( gameState == GAME_LOOP_STATE::GOAL_REACHED ) 
	{
		cout << "GAME_LOOP_STATE::WAVE_END" << endl;
		gameState = GAME_LOOP_STATE::WAVE_END;
		
		currentTimer = 0.0f;		
		Sound::StopSound(SOUNDS::GAME_MUSIC);
		Sound::PlayGameSound(SOUNDS::WIN_LEVEL);
	}

	//wave begin has shown long enough, lets gen the wave.
	if ( gameState == GAME_LOOP_STATE::WAVE_BEGIN && currentTimer > waveBeginTimer) 
	{
		cout << "GAME_LOOP_STATE::WAVE_RUNNING" << endl;
		gameState = GAME_LOOP_STATE::WAVE_RUNNING;

		currentTimer = 0.0f;		
	}

	//should we gen a new wave? 
	if ( gameState == GAME_LOOP_STATE::WAVE_END && currentTimer > waveEndTimer )
	{
		BeginWave();
	}

	//update power ups
	for ( int i = 0; i < powerUpList.size(); ++i )
	{
		powerUpList[i].Update(delta_);
		
		if  (Collision::CheckCollision(&player, &powerUpList[i]))
		{
			gui.AddScore(100, powerUpList[i].Pos());
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
	if ( gameState != GAME_LOOP_STATE::WAVE_BEGIN )
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
		Sound::PlayGameSound(SOUNDS::SPIT);
	}
}

void PSGameLoop::ExplosionEvent(Vector2 position_, Vector2 direction_, int score_)
{
	explosions.push_back(Explosion(position_, direction_));
	gui.AddScore(score_, position_);

	//30% chance of droping a pickup
	int chance = rand() % 10 + 1;
	if ( chance <= 3 )
	{
		//drop a pickup
		PowerUp powerUp;
		powerUp.Spawn(position_);
		powerUpList.push_back(powerUp);
	}

}
