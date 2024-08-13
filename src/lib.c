#pragma once

#include <string.h>
#define VERSION "0.1.0"

#include <stdint.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

// Disable warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

// #define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#pragma GCC diagnostic pop
#pragma GCC diagnostic pop

#define INCBIN_SILENCE_BITCODE_WARNING
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX bin_
#include <incbin.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8 byte;
typedef unsigned int uint;

typedef float f32;
typedef double f64;

typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Rectangle rect;

#define vec2new(X, Y) (vec2){(f32)(X), (f32)(Y)}
#define rectnew(X, Y, W, H) (rect){(f32)(X), (f32)(Y), (f32)(W), (f32)(H)}

#define vec2add Vector2Add
#define vec2sub Vector2Subtract
#define vec2subv Vector2SubtractValue
#define vec2mul Vector2Multiply
#define vec2div Vector2Divide

#define VEC2ZERO (vec2){0.0f, 0.0f}

static inline vec2 rectcenter(rect r) {
    return vec2new(
        r.x + (r.width / 2.0),
        r.y + (r.height / 2.0)
    );
}

static inline void toggle_fullscreen() {
    static i32 previous_width, previous_height;

    if (IsWindowFullscreen()) {
        ToggleFullscreen();
        SetWindowSize(previous_width, previous_height);
        return;
    }

    previous_width = GetScreenWidth();
    previous_height = GetScreenHeight();

    const i32 monitor = GetCurrentMonitor();
    const i32 monitor_w = GetMonitorWidth(monitor);
    const i32 monitor_h = GetMonitorHeight(monitor);

    SetWindowSize(monitor_w, monitor_h);
    ToggleFullscreen();    
}

static inline char* strtrim(char* s) {
    #define ISSPACE(C) ((C) == ' ' || (C) == '\n' || (C) == '\t')
    // Trim left
    while (ISSPACE(*s)) s++;

    const size_t len = strlen(s);
    for (size_t i = len - 1; i > 0; i--) {
        if (!ISSPACE(s[i])) {
            s[i] = '\0';
            return s;
        }
        s--;
    }

    return s;

    #undef ISSPACE
}
