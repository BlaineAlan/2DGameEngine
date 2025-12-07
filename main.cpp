#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "game_engine/engine.h"
#include "games/game.h"

int main(){    
    Engine engine;
    
    engine.init("Test game");

    MyGame game;

    engine.run(&game);

    return 0;
}