#include "Sound.h"
#include "bass.h"

HSTREAM Sound::soundSpit;
HSTREAM Sound::soundMonsterHit;
HSTREAM Sound::soundTreeHit;
HSTREAM Sound::soundStaminaUp;
HSTREAM Sound::soundSpitUp;


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
	soundSpit = BASS_StreamCreateFile(false, "./sound/spitpower.wav", 0,0,0);
	BASS_ChannelSetAttribute(soundSpit, BASS_ATTRIB_VOL, 0.3f);
	//BASS_ChannelPlay(myStream, false);
}

void Sound::PlayGameSound(SOUNDS sound_)
{
	if ( sound_ == SOUNDS::SPIT ) 
	{
		BASS_ChannelPlay(soundSpit, false);
	}
}