#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* HelloWorld = nullptr;

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init();

bool loadMedia();

void close();

SDL_Surface* loadSurface( std::string path );

SDL_Window* window = nullptr;
    
SDL_Surface* screenSurface = nullptr;

SDL_Surface* KeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

SDL_Surface* CurrentSurface = nullptr;

SDL_Renderer* renderer = nullptr;

SDL_Texture* loadTexture(std::string path);

SDL_Texture* texture = nullptr;


int main(){    
    if(!init()){
        std::cout << "Failed to initialize!\n";
    }else{
        if(!loadMedia()){
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

    return 0;
}

bool init(){
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

bool loadMedia(){
    bool success = true;

    texture = loadTexture("images/img.png");
    if(texture == nullptr){
        std::cout << "failed to load image!" << std::endl;
        success = false;
    }

    // KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/img.png");
    // if(KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr){
    //     std::cout << "Unable to load default image!" << std::endl;
    //     success = false;
    // }

    // KeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    // if(KeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr){
    //     std::cout << "Unable to load up image!" << std::endl;
    //     success = false;
    // }

    // KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    // if(KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr){
    //     std::cout << "Unable to load down image!" << std::endl;
    //     success = false;
    // }

    // KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    // if(KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr){
    //     std::cout << "Unable to load left image!" << std::endl;
    //     success = false;
    // }

    // KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    // if(KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr){
    //     std::cout << "Unable to load right image!" << std::endl;
    //     success = false;
    // }

    return success;
}

void close(){
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path){
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

SDL_Texture* loadTexture(std::string path){
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