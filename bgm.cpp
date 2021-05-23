#pragma once
#include "bgm.h"

void playm()
{
	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
}