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


bool Engine::init(std::string title){
    bool success = true;
    

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: \n" << SDL_GetError();
        success = false;
    }else{
        window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  
        if(window == nullptr){
            std::cout << "Window could not be created! SDL_Error: \n" << SDL_GetError();
            success = false;
        }else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr){
                std::cout << "Renderer could not be created!" << SDL_GetError();
                success = false;
            }else{
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags)){
                    std::cout << "SDL_image could not initialize!" << IMG_GetError();
                    success = false;
                }
            }
        }
    }

    return success;
}


void Engine::run(IGame* game){

    if(!init(game.get_name())){
    std::cout << "Failed to initialize!\n";
    }else{
        if(!game.loadMedia("")){
            std::cout << "Failed to load media!\n";
        }else{
            bool quit = false;

            SDL_Event e;
            
            Uint32 startTime = 0;

            std::stringstream timeText;

            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while(!quit){
                while(SDL_PollEvent( &e ) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                            CurrentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            CurrentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            CurrentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            CurrentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            CurrentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }

                    SDL_RenderClear(renderer);

                    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

                    SDL_RenderPresent(renderer);
        
                    // SDL_BlitSurface(CurrentSurface, nullptr, screenSurface, nullptr);
        
                    // SDL_UpdateWindowSurface(window);
                }

            }

        }
    }

    close();
}

void Engine::close(){
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* Engine::loadSurface( std::string path ){
    SDL_Surface* optimizedSurface = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to load image!" << IMG_GetError();
    }else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if(optimizedSurface == nullptr){
            std::cout << "Unable to optimize image!" << SDL_GetError();
        }

        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture* Engine::loadTexture(std::string path){
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to load image!" << IMG_GetError();
    }else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr){
            std::cout << "Unable to create texture!" << SDL_GetError();
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}