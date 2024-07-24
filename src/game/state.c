#pragma once

#include "game.h"
#include <time.h>

static const u8 random_bits[] = {
    0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0,
    0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1,
    1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0,
    1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1,
    0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
    1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1,
};

// Time management
static f32 one_second_timer = 0.0f;
static f32 one_minute_timer = 0.0f;
static f32 ten_second_timer = 0.0f;
static time_t now;
static struct tm* current_time;

static bool _game_running = true;
static f32 dt;
static i32 screen_w, screen_h;
static vec2 mouse_pos, mouse_delta;
static f32 mouse_wheel;
static GameState state;

FN void state_update() {
    dt = GetFrameTime();
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
    mouse_pos = GetMousePosition();
    mouse_delta = GetMouseDelta();
    mouse_wheel = GetMouseWheelMove();

    one_second_timer += dt;
    one_minute_timer += dt;
    ten_second_timer += dt;
    if (one_second_timer > 1.0) one_second_timer = 0.0f;
    if (one_minute_timer > 60.0) one_minute_timer = 0.0f;
    if (ten_second_timer > 10.0) ten_second_timer = 0.0f;
}

FN void update_time() {
    now = time(NULL);
    current_time = localtime(&now);
}