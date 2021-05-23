#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include "windows.h"
using namespace std;
#include "scoreFromFile.h"
#include "udlr.h"
#include "surface.h"
#include "Plate.h"

void start_new_play(void);

void end_the_game(float score);
bool is_time_up(std::chrono::time_point<std::chrono::system_clock> start, float _elapsed);
