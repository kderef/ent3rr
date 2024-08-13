#pragma once

#include "game/game.h"
#include <time.h>
#include "state/time.c"

static i32 prev_font_size;
static bool st_game_should_close = false;
static f32 dt;
static i32 screen_w, screen_h;
static vec2 mouse_pos, mouse_delta;
static f32 mouse_wheel;
static enum gamestate state;

FN void state_update() {
    dt = GetFrameTime();
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
    mouse_pos = GetMousePosition();
    mouse_delta = GetMouseDelta();
    mouse_wheel = GetMouseWheelMove();

    timer_tick(dt);
   
}

FN void save_font_size() {
    prev_font_size = GuiGetStyle(0, TEXT_SIZE);
}

FN void restore_font_size() {
    GuiSetStyle(0, TEXT_SIZE, prev_font_size);
}
