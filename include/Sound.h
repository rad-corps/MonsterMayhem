#pragma once

#include "bass.h"

enum SOUNDS
{
	SPIT,
	MONSTER_HIT,
	TREE_HIT,
	STAMINA_UP,
	SPIT_UP
};

class Sound
{
private:
	Sound(void);
	
public:
	~Sound(void);

	static void Initialise();
	static void PlayGameSound(SOUNDS);

	static HSTREAM soundSpit;
	static HSTREAM soundMonsterHit;
	static HSTREAM soundTreeHit;
	static HSTREAM soundStaminaUp;
	static HSTREAM soundSpitUp;
};

