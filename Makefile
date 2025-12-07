OBJS = main.cpp game_engine/engine.cpp games/game.cpp

CC = g++

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)