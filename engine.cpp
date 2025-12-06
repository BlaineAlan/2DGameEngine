#include <SDL2/SDL.h>
#include <SDL2/SDL_test_images.h>
#include <iostream>
#include <stdio.h>


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


int main(){    
    if(!init()){
        std::cout << "Failed to initialize!\n";
    }else{
        if(!loadMedia()){
            std::cout << "Failed to load media!\n";
        }else{
            bool quit = false;

            SDL_Event e;

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
        
                    SDL_BlitSurface(CurrentSurface, nullptr, screenSurface, nullptr);
        
                    SDL_UpdateWindowSurface(window);
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
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;

    KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/h.bmp");
    if(KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr){
        std::cout << "Unable to load default image!" << std::endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if(KeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr){
        std::cout << "Unable to load up image!" << std::endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if(KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr){
        std::cout << "Unable to load down image!" << std::endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if(KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr){
        std::cout << "Unable to load left image!" << std::endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if(KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr){
        std::cout << "Unable to load right image!" << std::endl;
        success = false;
    }

    return success;
}

void close(){
    SDL_FreeSurface(HelloWorld);
    HelloWorld = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to load image! SDL Error: \n" << path.c_str() << SDL_GetError(); 
    }
    return loadedSurface;
}