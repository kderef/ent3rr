#pragma once

#include <stdint.h>
#include <raymath.h>
#include <raylib.h>
#include <raygui.h>
#include <stdbool.h>

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

static u32 xorshift_state;

u32 xorshift32() {
	u32 x = xorshift_state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return xorshift_state = x;
}