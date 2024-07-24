CC = gcc
CFLAGS = -Wall -Wextra
ILFLAGS = -Iext/raygui/src -Iext/raylib/src -Isrc/ -Iext/incbin -Lext/raylib/src -lraylib
DEBUG_FLAGS = -O0 -DDEBUG
RELEASE_FLAGS = -O3 -s

WINDRES = windres
RESOURCE_COMMAND = $(WINDRES) res/resource.rc -o bin/resource.o

IMPL = src/game/game.c
MAIN = src/main.c
EXTRA = 
BIN = bin/ENT3RR

ifeq ($(OS), Windows_NT)
	CFLAGS += -lgdi32 -lwinmm
	RELEASE_FLAGS += -mwindows
	EXTRA += bin/resource.o
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		CFLAGS += -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif
endif

default: release

debug: $(MAIN)
	$(CC) $(MAIN) $(EXTRA) -o $(BIN) $(ILFLAGS) $(CFLAGS) $(DEBUG_FLAGS)

release: $(MAIN)
	-$(RESOURCE_COMMAND)
	$(CC) $(MAIN) $(EXTRA) -o $(BIN) $(ILFLAGS) $(CFLAGS) $(RELEASE_FLAGS)

run:
	$(BIN)

.PHONY: debug release run
