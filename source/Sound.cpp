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
HSTREAM Sound::soundGameMusic;
HSTREAM Sound::soundMenuMusic;
HSTREAM Sound::soundRestartScreen;
HSTREAM Sound::soundGameOver;

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
	soundSpit.push_back(BASS_StreamCreateFile(false, "./sound/spit.mp3", 0,0,0));
	soundSpit.push_back(BASS_StreamCreateFile(false, "./sound/spit.mp3", 0,0,0));
	
	soundMonsterHit = BASS_StreamCreateFile(false, "./sound/hit.mp3", 0,0,0);
	soundTreeHit    = BASS_StreamCreateFile(false, "./sound/tree_hit.mp3", 0,0,0);	
	soundExplosion  = BASS_StreamCreateFile(false, "./sound/explosion.mp3", 0,0,0);	
	soundSpitUp  = BASS_StreamCreateFile(false, "./sound/spitup.mp3", 0,0,0);	
	soundStaminaUp  = BASS_StreamCreateFile(false, "./sound/staminaup.mp3", 0,0,0);	
	soundPlayerDeath  = BASS_StreamCreateFile(false, "./sound/player_death.mp3", 0,0,0);	
	soundWinLevel = BASS_StreamCreateFile(false, "./sound/level_complete.mp3", 0,0,0);	
	soundGameMusic = BASS_StreamCreateFile(false, "./sound/game_music.mp3", 0,0,0);	
	soundMenuMusic = BASS_StreamCreateFile(false, "./sound/menu_music.mp3", 0,0,0);	
	soundRestartScreen = BASS_StreamCreateFile(false, "./sound/restart_screen.mp3", 0,0,0);	
	soundGameOver = BASS_StreamCreateFile(false, "./sound/game_over.mp3", 0,0,0);	

	BASS_ChannelSetAttribute(soundSpit[0], BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundSpit[1], BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundMonsterHit, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundTreeHit, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundExplosion, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundSpitUp, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundStaminaUp, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundPlayerDeath, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundWinLevel, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundGameMusic, BASS_ATTRIB_VOL, 0.35f);
	BASS_ChannelSetAttribute(soundMenuMusic, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundRestartScreen, BASS_ATTRIB_VOL, 0.6f);
	BASS_ChannelSetAttribute(soundGameOver, BASS_ATTRIB_VOL, 0.6f);
	
	//BASS_ChannelPlay(myStream, false);
}

void Sound::StopSound(SOUNDS sound_)
{
	if ( sound_ == SOUNDS::GAME_MUSIC)
	{
		BASS_ChannelStop(soundGameMusic);
	}
	if ( sound_ == SOUNDS::MENU_MUSIC)
	{
		BASS_ChannelStop(soundMenuMusic);
	}
	if ( sound_ == SOUNDS::RESTART_SCREEN_MUSIC )
	{
		BASS_ChannelStop(soundRestartScreen);
	}
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
	if ( sound_ == SOUNDS::GAME_MUSIC)
	{
		BASS_ChannelPlay(soundGameMusic, true);
	}
	if ( sound_ == SOUNDS::MENU_MUSIC)
	{
		BASS_ChannelPlay(soundMenuMusic, true);
	}
	if ( sound_ == SOUNDS::RESTART_SCREEN_MUSIC)
	{
		BASS_ChannelPlay(soundRestartScreen, true);
	}
	if ( sound_ == SOUNDS::GAME_OVER_MUSIC)
	{
		BASS_ChannelPlay(soundGameOver, true);
	}
}