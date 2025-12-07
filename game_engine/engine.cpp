#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "engine.h"

Engine::Engine() {}

Engine::~Engine() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool Engine::init(const char* title){
    bool success = true;
    

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: \n" << SDL_GetError();
        success = false;
    }else{
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  
        if(window == nullptr){
            std::cout << "Window could not be created! SDL_Error: \n" << SDL_GetError();
            success = false;
        }else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr){
                std::cout << "Renderer could not be created!" << SDL_GetError();
                success = false;
            }
        }
    }

    return success;
}

void Engine::run(IGame* game){
    bool quit = false;

    game->loadMedia(renderer);

    while(!quit){
        SDL_Event e;
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }


        SDL_RenderClear(renderer);

        game->render(renderer);

        SDL_RenderPresent(renderer);

    }

}