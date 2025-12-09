OBJS = main.cpp game_engine/engine.cpp games/game.cpp

CC = g++

CXXFLAGS = -std=c++17

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)