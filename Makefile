CC = g++
RAYGUI_CC = gcc
CFLAGS = -Wall -Wextra
FRAMEWORKS =
IFLAGS = -Iext/raygui/src -Iext/raylib/src -Isrc/ -Iext/incbin 
LFLAGS = -Lext/raylib/src -lraylib
DEBUG_FLAGS = -O0 -DDEBUG
RELEASE_FLAGS = -O3 -s

WINDRES = windres
RESOURCE_COMMAND = $(WINDRES) res/resource.rc -o bin/resource.o

IMPL = src/game/game.c
MAIN = src/main.c
EXTRA = 
BIN = bin/ENT3RR

RM = rm
TOUCH = touch

ifeq ($(OS), Windows_NT)
	CFLAGS += -lgdi32 -lwinmm
	RELEASE_FLAGS += -mwindows
	EXTRA += bin/resource.o
	TOUCH = echo.>
	RM = del
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S), Darwin))
		FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif
endif

default: release

raygui:
	$(RAYGUI_CC) $(IFLAGS) -O3 -s -c -DRAYGUI_IMPLEMENTATION ext/raygui/src/raygui.h -o lib/raygui.o
	

libgame:
	$(CC) $(DEBUG_FLAGS) $(FRAMEWORKS) $(IFLAGS) $(LFLAGS) -fPIC -shared src/game/game.c -o lib/libgame.so $(CFLAGS) $(LFLAGS)

debug: libgame raygui
	$(CC) $(MAIN) $(EXTRA) -o $(BIN) $(IFLAGS) $(CFLAGS) $(DEBUG_FLAGS)

release: $(MAIN) raygui
	-$(RESOURCE_COMMAND)
	$(CC) $(MAIN) $(EXTRA) -o $(BIN) $(LFLAGS) $(IFLAGS) $(CFLAGS) $(RELEASE_FLAGS)

release_test: $(MAIN) raygui
	-$(RESOURCE_COMMAND)
	$(CC) -DRELEASE_TEST $(MAIN) $(EXTRA) -o $(BIN) $(LFLAGS) $(IFLAGS) $(CFLAGS) $(RELEASE_FLAGS) -DDEBUG

run:
	$(BIN)
	-$(RM) lib/*

.PHONY: libgame debug release run raygui
