#include "game.h"
#include "menu.c"
#include "state.c"
#include "res.c"

/// Set target FPS
FN void game_set_fps(int fps) {
    SetTargetFPS(fps);
}

/// Close the window
FN void game_close() {
    CloseAudioDevice();
    CloseWindow();
}

/// Returns false if the game should quit
FN bool game_running() {
    return _game_running;
}


/// Open the window and set the initial game state
FN void game_init(uint flags, int w, int h, const char* title) {
    SetConfigFlags(flags);
    InitWindow(w, h, title);
    InitAudioDevice();
}

/// Load all the data
FN void game_load() {
    textures_load();
    fonts_load();
}

/// Unload all assets, before game_close()
FN void game_unload() {
    fonts_unload();
    textures_unload();
}

/// Update state, before drawing
FN void game_update() {
    _game_running ^= WindowShouldClose();
    state_update();

    switch (state) {
        case GAME_MENU:
            menu_update();
            break;
    }
}

/// Draw the game to the screen
FN void game_draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (state) {
        case GAME_MENU:
            menu_draw();
            break;
    }


#ifdef DEBUG
    DrawFPS(0, 0);
#endif

    EndDrawing();
}

