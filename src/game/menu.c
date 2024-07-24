#pragma once

#include "game.h"
#include "lib.c"
#include "state.c"
#include "res.c"

FN void menu_draw_background() {
    const Color tint = {0, 255, 0, 255};

    const f32 scale = 10.0;
    const rect screen = rectnew(0, 0, screen_w, screen_h);
    const Texture brick = textures[TX_BRICK];

    const f32 w_scaled = brick.width * scale;
    const f32 h_scaled = brick.height * scale;

    const i32 repeat_x = ceilf((f32)screen_w / w_scaled);
    const i32 repeat_y = ceilf((f32)screen_h / h_scaled);
    
    for (i32 y = 0; y < repeat_y; y++)
        for (i32 x = 0; x < repeat_x; x++)
            DrawTextureEx(brick, vec2new(x * w_scaled, y * h_scaled), 0.0, scale, tint);
}

FN void menu_draw_text_overlay() {
    static float offset_x = 0.0f; // Horizontal offset for scrolling
    static float offset_y = 0.0f; // Vertical offset for scrolling
    static float scroll_speed = 10.0f; // Speed of scrolling

    const f32 char_size = 20.0;  // Size of each character
    const i32 cols = screen_w / char_size + 2; // Add extra columns for smooth scrolling
    const i32 rows = screen_h / char_size + 2; // Add extra rows for smooth scrolling
    const Color tint = {0, 255, 0, 40};  // Semi-transparent white
    uint rand_index = GetRandomValue(0, sizeof(random_bits));

    // Update the scrolling offsets
    offset_x += scroll_speed * GetFrameTime();
    offset_y += scroll_speed * GetFrameTime();

    // Reset offsets to avoid floating point precision issues
    if (offset_x >= char_size) offset_x -= char_size;
    if (offset_y >= char_size) offset_y -= char_size;

    for (i32 y = 0; y < rows; y++) {
        for (i32 x = 0; x < cols; x++) {
            // Generate a random character ('0' or '1')
            rand_index += 1;
            if (rand_index == sizeof(random_bits)) rand_index = 0;
            char number[2] = {random_bits[rand_index] + '0', '\0'};
            // Draw the number at the position with the offset applied
            DrawTextEx(font_01, number, vec2new(x * char_size - offset_x, y * char_size - offset_y), char_size, 1.0, tint);
        }
    }
}

FN void menu_draw_title() {
    static f32 timer = 0.0;
    timer += dt;
    if (timer > 1.0) timer = 0.0;

    const char* title = (timer < 0.5)? "ENT3RR " : "ENT3RR_";

    const f32 title_size = Clamp(screen_w * 0.05, 150.0, 500.0);
    const vec2 title_dims = MeasureTextEx(font_01, title, title_size, 1.0);
    const Color tint = { 0, 228, 48, 255 };

    DrawTextEx(font_01, title, vec2new(
        (f32)(screen_w / 2) - title_dims.x / 2.0,
        title_size
    ), title_size, 1.0, tint);
}

FN void menu_draw() {
    menu_draw_background();
    menu_draw_text_overlay();
    menu_draw_title();
}

FN void menu_update() {
    
}