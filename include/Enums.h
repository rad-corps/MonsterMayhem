#pragma once

//put things we want for whole project here
#include <iostream>
using namespace std;

enum PROGRAM_STATES
{
	MAIN_MENU,
	GAME_LOOP
};

enum POWER_UP_TYPE
{
	SPIT_FREQUENCY,
	SPEED_UP
};

#define SCREEN_W 1680
#define SCREEN_H 1050

#define PLAYER_W 64
#define PLAYER_H 64

#define PLAYER_SPEED 150.0

#define TERRAIN_COLS 32
#define TERRAIN_ROWS 32
#define TERRAIN_W 256
#define TERRAIN_H 256

#define BATTLE_FIELD_W TERRAIN_W * TERRAIN_COLS
#define BATTLE_FIELD_H TERRAIN_H * TERRAIN_ROWS

#define LOOGIE_RELOAD 0.6
#define LOOGIE_W 16
#define LOOGIE_H 16
#define LOOGIE_VELOCITY 31.0
#define SPIT_POOL 20

#define POWER_UP_W 64
#define POWER_UP_H 64