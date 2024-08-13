#pragma once

#include "lib.c"
#include "game/game.h"

static u32 rand_state;
FN u32 xorshift32(u32* state) {
    u32 x = *state;
    	x ^= x << 13;
    	x ^= x >> 17;
    	x ^= x << 5;
    return *state = x;
}
