#include <raylib.h>
#include "lib.c"

#include "game/game.c"

int main(void) {
    const uint flags = FLAG_WINDOW_RESIZABLE;

    game_init(flags, 800, 600, "ENT3RR");
    game_load();

#ifndef DEBUG
    game_set_fps(240);
#endif

    while (game_running()) {
        game_update();
        game_draw();
    }

    game_unload();
    game_close();

    return 0;
}