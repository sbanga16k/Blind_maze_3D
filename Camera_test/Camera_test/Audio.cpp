#include "Audio.h"
#include <iostream>
#include "fssimplewindow.h"

using namespace std;

//YsSoundPlayer::SoundData Sounds::wavData;
//bool Sounds::soundOK = false;
YsSoundPlayer Sounds::soundPlayer;
int key;

void Sounds::loadSound(const char Sound[], int index)
{
	if (YSOK != wavData[index].LoadWav(Sound))
	{
		cout << "Failed to read sound file " << Sound << endl;;
		soundOK = false;
	}
	else
		soundOK = true;
}

void Sounds::playSound(int index)
{
	if (soundOK)
		soundPlayer.PlayBackground(wavData[index], true);
}

void Sounds::movementSound()
{
	//YsSoundPlayer SoundPlayer;
	//YsSoundPlayer::SoundData wav;
	//soundPlayer.Start();
	FsPollDevice();
	key = FsInkey();
	if (key == FSKEY_W)
	{
		//loadSound("FootSteps.wav");
		playSound(3);
	}
	else if (key == FSKEY_A)
	{
		//loadSound("FootSteps.wav");
		playSound(3);
	}
	else if (key == FSKEY_S)
	{
		//loadSound("FootSteps.wav");
		playSound(3);
	}
	else if (key == FSKEY_D)
	{
		//loadSound("FootSteps.wav");
		playSound(3);
	}
}

