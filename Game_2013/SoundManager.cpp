#include "SoundManager.h"

SoundManager::SoundManager()
{
	FMOD::System_Create(&fmodsystem);
	fmodsystem->init(5, FMOD_INIT_NORMAL, 0);

}

void SoundManager::loadSounds()
{
	fmodsystem->createSound("Synthetica.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM, 0, &sound1);
	fmodsystem->createSound("Play.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM, 0, &sound2);
	fmodsystem->createSound("Game.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM, 0, &sound3);
	fmodsystem->createSound("Exit.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM, 0, &sound4);
}

void SoundManager::menuMusic()
{
	fmodsystem->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel0);
	channel0->setPosition(0, FMOD_TIMEUNIT_MS);
	
}

void SoundManager::optionMusic()
{
	fmodsystem->playSound(FMOD_CHANNEL_FREE, sound2, false, &channel1);
}

void SoundManager::gameMusic()
{
	fmodsystem->playSound(FMOD_CHANNEL_FREE, sound3, false, &channel2);
}

void SoundManager::exitMusic()
{
	fmodsystem->playSound(FMOD_CHANNEL_FREE, sound4, false, &channel3);
}

void SoundManager::releaseMenu()
{
	sound1->release();
	//fmodsystem->close();
	//fmodsystem->release();
}

void SoundManager::releaseGame()
{
	sound3->release();
}

void SoundManager::releaseExit()
{
	sound4->release();
}
