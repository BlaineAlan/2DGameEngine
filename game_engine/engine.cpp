/**
 * @file engine.cpp
 * @author Blaine Cochensparger
 * @brief cpp file for my 2D game engine class. Right now all the functions are within this file, but eventually the engine may be split up into multiple parts
 * 
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "engine.h"
#include "../games/ball.h"

Engine::Engine() {}

//Destroys everything necessary, SDL, IMG, and TTF
Engine::~Engine() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Engine::init(const char* title){
    bool success = true;
    
    //make sure SDL initializes without fail
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: \n" << SDL_GetError();
        success = false;
    }else{
        //make sure window initializes withoout fail
        //set windoow to have the given screen height, width, and title
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  
        if(window == nullptr){
            std::cout << "Window could not be created! SDL_Error: \n" << SDL_GetError();
            success = false;
        }else{
            //make sure renderer initializes without fail
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr){
                std::cout << "Renderer could not be created!" << SDL_GetError();
                success = false;
            }

        }
    }

    //if anything failed, return false
    return success;
}

void Engine::run(IGame* game){
    //keep track of if the user quit the program
    bool quit = false; 
    //keep track of how much has changed
    float dt = 0.0f;

    //initialize the game and load any media from it using the renderer
    game->init(*this);
    game->loadMedia(renderer);

    /* MAIN LOOP */
    //while the user hasn't quit the game
    while(!quit){
        //start our dt clock
        auto startTime = std::chrono::high_resolution_clock::now();

        //initialize an event e
        SDL_Event e;
        while(SDL_PollEvent( &e ) != 0){
            //if the user clicks the quit button, exit the game
            if(e.type == SDL_QUIT){
                quit = true;
            //else, allow the game itself to handle the events from the user
            }else{
                game->handleEvent(e);
            }
        }

        //update the game using how much time has passed
        game->update(dt);

        //render to the screen
        SDL_RenderClear(renderer);
        game->render(renderer);
        SDL_RenderPresent(renderer);

        //stop our dt time so it can be restarted
        auto stopTime = std::chrono::high_resolution_clock::now();
	    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }

}
