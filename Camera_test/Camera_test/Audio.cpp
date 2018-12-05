#include "Audio.h"
#include <iostream>
#include "fssimplewindow.h"

using namespace std;

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

void Sounds::playerSound()
{
	FsPollDevice();

	key = FsInkey();
	if (FsGetKeyState(FSKEY_W))
	{
		playSound(3);
	}
	else if (FsGetKeyState(FSKEY_A))
	{
		playSound(3);
	}
	else if (FsGetKeyState(FSKEY_S))
	{
		playSound(3);
	}
	else if (FsGetKeyState(FSKEY_D))
	{
		playSound(3);
	}
}