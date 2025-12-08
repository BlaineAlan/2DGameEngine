/**
 * @file main.cpp
 * @author Blaine Cochensparger
 * @brief Main file for running the Pong game using my 2D game engine. 
 * 
 */

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
    //Create the engine
    Engine engine;
    //Initialize it with a window title of "Pong"
    engine.init("Pong");

    //Create Pong using the engine
    MyGame game(engine);
    
    //Run the game using the engine
    engine.run(&game);

    return 0;
}