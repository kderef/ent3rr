#include "game.h"
#include "menu.c"
#include "raylib.h"
#include "state.c"
#include "res.c"
#include "ui/style.c"
#include "cmd.c"

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
FN bool game_should_close() {
    return st_game_should_close;
}


/// Open the window and set the initial game state
FN void game_init(uint flags, int w, int h, const char* title) {
    // Seed random
    rand_state = time(NULL);
    
    SetConfigFlags(flags);
    InitWindow(w, h, title);
    SetWindowMinSize(w, h);
    InitAudioDevice();

    SetExitKey(0);
}

/// Load all the data
FN void game_load() {
    SetWindowIcon(window_icon_load());

    textures_load();
    fonts_load();
    ui_load_style_terminal(&font_01);
}
#define game_reload game_load

/// Unload all assets, before game_close()
FN void game_unload() {
    fonts_unload();
    textures_unload();
    window_icon_unload();
    cmd_free();
}

/// Update state, before drawing
FN void game_update() {
    st_game_should_close = st_game_should_close || WindowShouldClose();
    state_update();

    if (IsKeyPressed(KEY_F11)) {
        toggle_fullscreen();
    }

    switch (state) {
        case GAME_MENU: break;
        case GAME_CMD:
            cmd_update();
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
        case GAME_CMD:
            cmd_draw();
            break;
    }


#ifdef DEBUG
    static char fps_buf[64];
    snprintf(fps_buf, sizeof(fps_buf) / sizeof(char), "FPS: %d", GetFPS());
    DrawText(fps_buf, 0, 0, 20, PURPLE);
#endif

    // DrawRectangle(0, 0, 200, 100, BLACK);

    EndDrawing();
}

