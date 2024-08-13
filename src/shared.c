#pragma once

#include "shared.h"

#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

// Posix system
#if defined(__unix__) || defined(__APPLE__)

#include <unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <limits.h>

#define LIB_PATH "lib/libgame.so"
#define DLSYM(FN) FN = (lib_##FN)dlsym(lib_game, #FN)

#define LIB_STRFT "lib/libgame-%H_%M.so"

// DLL loading
static void* lib_game = NULL;
static char lib_path[PATH_MAX] = {0};

char* update_lib_path() {
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);

    strftime(lib_path, PATH_MAX, LIB_STRFT, tm);

    return lib_path;
}

int lib_move(char* lib_path_old, char* lib_path_new) {
#ifdef _WIN32
    #define MV "rename"
#else
    #define MV "mv"
#endif

    char* old = lib_path_old;

    struct stat _file;
    if (stat(LIB_PATH, &_file) == 0) {
        old = LIB_PATH;
    }
    
    // Move it
    char cmd[PATH_MAX * 3] = {0};
    snprintf(cmd, sizeof(cmd), MV" '%s' '%s'", old, lib_path_new);
    fprintf(stderr, "[HOTRELOAD] [CMD] %s\n", cmd);

    return system(cmd);
}

void lib_load() {
    // Save old path
    char lib_path_old[PATH_MAX] = {0};
    if (lib_path[0] == '\0') {
        strncpy(lib_path_old, LIB_PATH, PATH_MAX);
    }
    else strncpy(lib_path_old, lib_path, PATH_MAX);
    
    // Calculate new path
    char* lib_path_new = update_lib_path();
    
    fprintf(stderr, "[HOTRELOAD] Renamed lib path: '%s' -> %s\n", lib_path_old, lib_path_new);

    int success = lib_move(lib_path_old, lib_path_new);

    if (success != 0) {
        fprintf(stderr, "[HOTRELOAD] [ERROR] failed to move library.\n");
        exit(1);
    }
    
    // Reload
    fprintf(stderr, "[HOTRELOAD] Loading lib '%s'...", lib_path_new);
    if (lib_game) {
        dlclose(lib_game);
    }
    lib_game = dlopen(lib_path_new, RTLD_LAZY  | RTLD_LOCAL);
    if (!lib_game){
        fprintf(stderr, "Failed to load game library: %s\n", dlerror());
        exit(1);
    }

    DLSYM(game_init);
    DLSYM(game_load);
    DLSYM(game_draw);
    DLSYM(game_close);
    DLSYM(game_unload);
    DLSYM(game_update);
    DLSYM(game_should_close);
    
    fprintf(stderr, "done\n");
}

void lib_unload() {
    fprintf(stderr, "[HOTRELOAD] Unloading lib '%s'...", LIB_PATH);
    if (lib_game) {
        dlclose(lib_game);
        lib_game = NULL;
    }
    fprintf(stderr, "done\n");
}

void lib_reload() {
    fprintf(stderr, "\n***************************\n");
    fprintf(stderr, "[HOTRELOAD] Unloading game...\n");
    game_unload();
    fprintf(stderr, "[HOTRELOAD] done\n");

    lib_unload();
    lib_load();

    fprintf(stderr, "[HOTRELOAD] Loading game...\n");
    game_load();
    fprintf(stderr, "[HOTRELOAD] done\n");
    printf("***************************\n");
}

static time_t lib_last_write = 0;
bool lib_changed() {
    struct stat file;

    if (stat(LIB_PATH, &file) == 0) {
        lib_last_write = file.st_mtime;
        return true;
    }
    else if (stat(lib_path, &file) == 0) {
        if (file.st_mtime != lib_last_write) {
            lib_last_write = file.st_mtime;
            return true;
        }
    }
    else {
        perror("[HOTRELOAD] stat");
    }

    return false;
}

#else // is not posix

#include <windows.h>

#define DLSYM(FN) FN = (lib_##FN)GetProcAddress(lib_game, #FN)

static HMODULE lib_game = NULL;

void lib_load() {
    if (lib_game) {
        FreeLibrary(lib_game);
    }
    lib_game = LoadLibrary(LIB_PATH);
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
        fprintf(stderr, "Failed to load game library: %ld\n", GetLastError());
        exit(1);
    }
}

void lib_unload() {
    if (lib_game) {
        FreeLibrary(lib_game);
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

static FILETIME lib_last_write = {0};
bool lib_changed() {
    WIN32_FILE_ATTRIBUTE_DATA file_info;

    if (GetFileAttributesEx(LIB_PATH, GetFileExInfoStandard, &file_info)) {
        if (CompareFileTime(&file_info.ftLastWriteTime, &lib_last_write) != 0) {
            lib_last_write = file_info.ftLastWriteTime;
            return true;
        }
    } else {
        fprintf(stderr, "Failed to get file attributes: %ld\n", GetLastError());
    }

    return false;
}

#endif // is posix
