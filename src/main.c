#define WINDOW_TITLE "ENT3RR"
#define WINDOW_W 800
#define WINDOW_H 600
#define FLAGS (FLAG_WINDOW_RESIZABLE)

#ifdef DEBUG
#include "shared.h"
#include <raylib.h>
#include "shared.c"
#else // Release
#define lib_load()
#define lib_unload()
#define lib_reload()
#define lib_changed() 0
#include "game/game.c"
#endif

// Library loading

int main(void) {
    // Load library and game
    lib_load();
    lib_changed();
    
    game_init(FLAGS, WINDOW_W, WINDOW_H, WINDOW_TITLE);
    game_load();

    while (!game_should_close()) {
        game_update();
        game_draw();

        if (lib_changed()) {
            lib_reload();
        }
    }

    game_unload();
    game_close();

    lib_unload();

    return 0;
}
