#pragma once

#include "game.h"
#include "lib.c"
#include "state.c"
#include "res.c"

#define CMD_FONT_SIZE_MIN 10
#define CMD_FONT_SIZE_MAX 70
#define HISTORY_MAX 4096

enum Path {
    PATH_HOME = 0,
    PATH_DOCS,
};

FN const char* path_str(enum Path p) {
    switch (p) {
        case PATH_HOME: return "/>";
        case PATH_DOCS: return "/docs/>";
        default: return "";
    }
}


static bool cmd_loaded = false;
static struct {
    enum Path path;
    size_t commands;
    i32 font_size;
    char* history[HISTORY_MAX];
} cmd = {0};

FN void cmd_init() {
    cmd.font_size = (CMD_FONT_SIZE_MAX - CMD_FONT_SIZE_MIN) / 2;
}

FN void cmd_free() {
    for (size_t i = 0; i < cmd.commands && i < HISTORY_MAX; i++) {
        free(cmd.history[i]);
    }
}

FN void cmd_update() {
    bool zoom_in = (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_EQUAL)) ||
        mouse_wheel > 0.0f;

    if (zoom_in && cmd.font_size < CMD_FONT_SIZE_MAX) {
        cmd.font_size += 1;
    }
    else {
        bool zoom_out = (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_MINUS)) ||
            mouse_wheel < 0.0f;
        
        if (zoom_out && cmd.font_size > CMD_FONT_SIZE_MIN) {
            cmd.font_size -= 1;
        }
    }
}

FN void cmd_run(char* command) {
    char* trimmed = strtrim(command);
    TraceLog(LOG_ERROR, "%s", trimmed);
}

FN void cmd_draw() {
    //Background is already cleared to BLACK
    // prompt style: />

    bool font_size_changed = cmd.font_size != prev_font_size;

    if (font_size_changed) {
        save_font_size();
        GuiSetStyle(0, TEXT_SIZE, cmd.font_size);
    }

    const char* cwd = path_str(cmd.path);
    const size_t cwd_len = strlen(cwd);
    const i32 offset = cwd_len * cmd.font_size;

    rect bounds = {
        .x = 0,
        .y = 0,
        .width = offset,
        .height = cmd.font_size
    };

    GuiDrawText(cwd, bounds, TEXT_ALIGN_CENTER, YELLOW);

    bounds.x += offset;
    bounds.width = screen_w - offset;

    static char command[512];
    if (GuiTextBox(bounds, command, cmd.font_size, true)) {
        cmd_run(command);

        // Reset command
        command[0] = '\0';
    }

    if (font_size_changed) restore_font_size();
}
