#pragma once

#include "bass.h"
#include <vector>

using namespace std;

enum SOUNDS
{
	SPIT,
	MONSTER_HIT,
	MONSTER_EXPLOSION,
	TREE_HIT,
	STAMINA_UP,
	SPIT_UP,
	PLAYER_DEATH,
	WIN_LEVEL,
	GAME_MUSIC,
	MENU_MUSIC,
	RESTART_SCREEN_MUSIC,
	GAME_OVER_MUSIC,
	PICKUP_DROP
};

class Sound
{
private:
	Sound(void);
	
public:
	~Sound(void);

	static void Initialise();
	static void PlayGameSound(SOUNDS);
	static void StopSound(SOUNDS);

	static vector<HSTREAM> soundSpit;
	static int currentSpitNum;
	static HSTREAM soundMonsterHit;
	static HSTREAM soundTreeHit;
	static HSTREAM soundStaminaUp;
	static HSTREAM soundSpitUp;
	static HSTREAM soundExplosion;
	static HSTREAM soundPlayerDeath;
	static HSTREAM soundWinLevel;
	static HSTREAM soundGameMusic;
	static HSTREAM soundMenuMusic;
	static HSTREAM soundRestartScreen;
	static HSTREAM soundGameOver;
	static HSTREAM soundPickupDrop;
};

