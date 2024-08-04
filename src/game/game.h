#pragma once

#include "lib.c"

#ifdef DEBUG
#define FN
#else
#define FN static inline
#endif

enum gamestate {
    GAME_MENU = 0,
    GAME_CMD,
};

FN void game_init(uint flags, int w, int h, const char* title);
FN void game_load();
FN void game_set_fps(int fps);
FN void game_update();
FN void game_draw();
FN void game_close();
FN void game_unload();
FN bool game_should_close();

FN void menu_draw();
