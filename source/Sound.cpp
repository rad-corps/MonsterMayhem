#include "Sound.h"
#include "bass.h"

vector<HSTREAM> Sound::soundSpit;
HSTREAM Sound::soundMonsterHit;
HSTREAM Sound::soundTreeHit;
HSTREAM Sound::soundStaminaUp;
HSTREAM Sound::soundSpitUp;
HSTREAM Sound::soundExplosion;
HSTREAM Sound::soundPlayerDeath;
HSTREAM Sound::soundWinLevel;

int Sound::currentSpitNum = 0;

Sound::Sound(void)
{
}


Sound::~Sound(void)
{
}

void Sound::Initialise()
{
	BASS_Init(-1,44100,0,0,0);
	
	//create all the sounds
	//HSTREAM myStream = BASS_StreamCreateFile(false,"./sound/spitpower.wav",0,0,0);
	soundSpit.push_back(BASS_StreamCreateFile(false, "./sound/spit.wav", 0,0,0));
	soundSpit.push_back(BASS_StreamCreateFile(false, "./sound/spit.wav", 0,0,0));
	
	soundMonsterHit = BASS_StreamCreateFile(false, "./sound/hit.wav", 0,0,0);
	soundTreeHit    = BASS_StreamCreateFile(false, "./sound/tree_hit.wav", 0,0,0);	
	soundExplosion  = BASS_StreamCreateFile(false, "./sound/explosion.wav", 0,0,0);	
	soundSpitUp  = BASS_StreamCreateFile(false, "./sound/spitup.wav", 0,0,0);	
	soundStaminaUp  = BASS_StreamCreateFile(false, "./sound/staminaup.wav", 0,0,0);	
	soundPlayerDeath  = BASS_StreamCreateFile(false, "./sound/player_death.wav", 0,0,0);	
	soundWinLevel = BASS_StreamCreateFile(false, "./sound/winlevel.wav", 0,0,0);	

	BASS_ChannelSetAttribute(soundSpit[0], BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundSpit[1], BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundMonsterHit, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundTreeHit, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundExplosion, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundSpitUp, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundStaminaUp, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundPlayerDeath, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundWinLevel, BASS_ATTRIB_VOL, 0.6f);
	//BASS_ChannelPlay(myStream, false);
}

void Sound::PlayGameSound(SOUNDS sound_)
{
	if ( sound_ == SOUNDS::SPIT ) 
	{
		BASS_ChannelPlay(soundSpit[currentSpitNum], true);
		currentSpitNum == 0 ? ++currentSpitNum : --currentSpitNum;
	}
	if ( sound_ == SOUNDS::MONSTER_HIT )
	{
		BASS_ChannelPlay(soundMonsterHit, true);
	}
	if ( sound_ == SOUNDS::TREE_HIT )
	{
		BASS_ChannelPlay(soundTreeHit, true);
	}
	if ( sound_ == SOUNDS::MONSTER_EXPLOSION )
	{
		BASS_ChannelPlay(soundExplosion, true);
	}
	if ( sound_ == SOUNDS::SPIT_UP)
	{
		BASS_ChannelPlay(soundSpitUp, true);
	}
	if ( sound_ == SOUNDS::STAMINA_UP)
	{
		BASS_ChannelPlay(soundStaminaUp, true);
	}
	if ( sound_ == SOUNDS::PLAYER_DEATH)
	{
		BASS_ChannelPlay(soundPlayerDeath, true);
	}
	if ( sound_ == SOUNDS::WIN_LEVEL)
	{
		BASS_ChannelPlay(soundWinLevel, true);
	}
}