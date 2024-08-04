#pragma once

#include "shared.h"
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

// Posix system
#if 1//defined(__unix__) || defined(__APPLE__)

#include <unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>

#define LIB_PATH "lib/libgame.so"
#define DLSYM(FN) FN = (lib_##FN)dlsym(lib_game, #FN)

// DLL loading

static void* lib_game = NULL;

void lib_load() {
    if (lib_game) {
        dlclose(lib_game);
    }
    lib_game = dlopen(LIB_PATH, 1);
    if (lib_game) {
        DLSYM(game_init);
        DLSYM(game_load);
        DLSYM(game_draw);
        DLSYM(game_close);
        DLSYM(game_unload);
        DLSYM(game_update);
        DLSYM(game_should_close);
    }
    else {
        fprintf(stderr, "Failed to load game library: %s\n", dlerror());
        exit(1);
    }
}
void lib_unload() {
    if (lib_game) {
        dlclose(lib_game);
        lib_game = NULL;
    }
}

void lib_reload() {
    game_unload();
    game_close();
    lib_unload();
    lib_load();
    game_init(FLAGS, WINDOW_W, WINDOW_H, WINDOW_TITLE);
    game_load();
}

static time_t lib_last_write = 0;
bool lib_changed() {
    struct stat file;

    if (stat(LIB_PATH, &file) == 0) {
        if (file.st_mtime != lib_last_write) {
            lib_last_write = file.st_mtime;
            return true;
        }
    } else {
        perror("stat");
    }

    return false;
}
#else // is not posix

#endif // is posix

// TODO: implement windows
