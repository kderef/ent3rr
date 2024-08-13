#pragma once

#include "game/game.h"
#include "lib.c"
#include <time.h>

// Time management
static time_t now;
static struct tm* current_time;

FN void update_time() {
    now = time(NULL);
    current_time = localtime(&now);
}

// Timers
static struct {
    f32 one_second;
    f32 one_minute;
    f32 ten_second;
} timer = {0};

FN void timer_tick(f32 dt) {
    #define tick(FIELD, MAX) \
        timer.FIELD += dt; \
        if (timer.FIELD > MAX) timer.FIELD = 0.0f

    tick(one_second, 1.0);

    #undef tick
}
