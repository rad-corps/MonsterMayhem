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
	WIN_LEVEL
};

class Sound
{
private:
	Sound(void);
	
public:
	~Sound(void);

	static void Initialise();
	static void PlayGameSound(SOUNDS);

	static vector<HSTREAM> soundSpit;
	static int currentSpitNum;
	static HSTREAM soundMonsterHit;
	static HSTREAM soundTreeHit;
	static HSTREAM soundStaminaUp;
	static HSTREAM soundSpitUp;
	static HSTREAM soundExplosion;
	static HSTREAM soundPlayerDeath;
	static HSTREAM soundWinLevel;
};

