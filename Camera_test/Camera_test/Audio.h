#pragma once

#include "yssimplesound.h"

class Sounds
{
public:
	YsSoundPlayer::SoundData wavData[5];
	//YsSoundPlayer::SoundData wavData;
	bool soundOK;
	static YsSoundPlayer soundPlayer;
public:
	void loadSound(const char Sound[], int index);
	void playSound(int index);
	void playerSound();
};