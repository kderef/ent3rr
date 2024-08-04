#pragma once

#include <stdbool.h>

#define define(TY, FN_NAME, ...) typedef TY (*lib_##FN_NAME)(__VA_ARGS__)

// Functions
define(void, game_init, unsigned int, int, int, const char*);
define(void, game_load);
define(void, game_update);
define(void, game_draw);
define(void, game_unload);
define(void, game_close);
define(bool, game_should_close);

// Pointers
static lib_game_init game_init;
static lib_game_load game_load;
static lib_game_draw game_draw;
static lib_game_close game_close;
static lib_game_unload game_unload;
static lib_game_update game_update;
static lib_game_should_close game_should_close;
