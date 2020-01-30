#include "FMOD/inc/fmod.hpp"
#include "FMOD/inc/fmod_errors.h"

class SoundManager
{
public:
	FMOD::System *fmodsystem;
	FMOD::Sound *sound1, *sound2, *sound3, *sound4;
	FMOD::Channel *channel0, *channel1, *channel2, 
				  *channel3, *channel4, *channel5;

	SoundManager();
	void loadSounds();
	void menuMusic();

	void gameMusic();
	void optionMusic();
	void exitMusic();
	
	void releaseMenu();
	void releaseGame();
	void releaseExit();

};