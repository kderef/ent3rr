#pragma once

#include "game.h"
#include <stdio.h>
#include "lib.c"

/*************************** COLORS ***************************/
static const Color
    FG_1 = {235, 219, 187, 255},
    FG_2 = {213, 196, 161, 255},
    FG_3 = {189, 174, 147, 255},
    FG_4 = {168, 153, 152, 255};


/*************************** TEXTURES ***************************/

#pragma GCC push_options
#pragma GCC optimize ("O2") // O3 causes Assembler error

#define INCLUDE_TEXTURE(FTYPE, IDX) do { \
        INCBIN(IDX, PATH_##IDX); \
        Image i = LoadImageFromMemory(FTYPE, bin_##IDX##_data, bin_##IDX##_size); \
        textures[IDX] = LoadTextureFromImage(i); \
        UnloadImage(i); \
    } while (0)

enum
{
    TX_BRICK,
    TX_MAX
};
#define PATH_TX_BRICK "res/brick.png"

static const char* TEXTURE_PATHS[TX_MAX] = {
    [TX_BRICK] = PATH_TX_BRICK
};

static Texture textures[TX_MAX] = {0};

FN void textures_load() {
    uint i;
#ifdef DEBUG
    for (i = 0; i < TX_MAX; i++) textures[i] = LoadTexture(TEXTURE_PATHS[i]);
#else
    INCLUDE_TEXTURE(".png", TX_BRICK);
#endif
}


FN void textures_unload() {
    for (uint i = 0; i < TX_MAX; i++) UnloadTexture(textures[i]);
}

/*************************** FONTS ***************************/
#define INCL_FONT_SIZE 200

#ifdef DEBUG
#define INCLUDE_FONT(NAME, _, PATH) NAME = LoadFontEx(PATH, INCL_FONT_SIZE, NULL, 0)
#else
#define INCLUDE_FONT(NAME, FTYPE, PATH) do {\
        INCBIN(NAME, PATH); \
        NAME = LoadFontFromMemory(FTYPE, bin_##NAME##_data, bin_##NAME##_size, INCL_FONT_SIZE, NULL, 0); \
    } while (0)
#endif

static Font font_ibm;

#define font_01 font_ibm

FN void fonts_load() {
    INCLUDE_FONT(font_ibm, ".otf", "res/ibm-dos-vga-9x16.ttf");
}

FN void fonts_unload() {
    UnloadFont(font_ibm);
}

/************** Window icon **************/

static Image window_icon;
FN Image window_icon_load() {
    INCBIN(window_icon, "res/icon.png");
    (void)bin_window_icon_end;
    return window_icon = LoadImageFromMemory(".png", bin_window_icon_data, bin_window_icon_size);
}

FN void window_icon_unload() {
    UnloadImage(window_icon);
}

#pragma GCC pop_options
