#ifndef ENGINE_H
#define ENGINE_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

class Engine;

class IGame {
    public:
        virtual ~IGame() {}

        virtual void init(Engine& engine) = 0;

        virtual void loadMedia(SDL_Renderer* renderer)  = 0;
        //virtual void update(float dt) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
};

class Engine{
    public:
        Engine();

        ~Engine();

        bool init(const char* title);

        void run(IGame* game);

        void close();

        SDL_Surface* loadSurface( std::string path );

        SDL_Texture* loadTexture(std::string path);


        int get_screen_h() const{
            return SCREEN_HEIGHT;
        }

        int get_screen_w() const{
            return SCREEN_WIDTH;
        }

    private:

        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;
        
        SDL_Surface* HelloWorld = nullptr;
        
        enum KeyPressSurfaces{
            KEY_PRESS_SURFACE_DEFAULT,
            KEY_PRESS_SURFACE_UP,
            KEY_PRESS_SURFACE_DOWN,
            KEY_PRESS_SURFACE_LEFT,
            KEY_PRESS_SURFACE_RIGHT,
            KEY_PRESS_SURFACE_TOTAL
        };
        
        SDL_Window* window = nullptr;
            
        SDL_Surface* screenSurface = nullptr;
        
        SDL_Surface* KeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
        
        SDL_Surface* CurrentSurface = nullptr;
        
        SDL_Renderer* renderer = nullptr;
        
        SDL_Texture* texture = nullptr;
};


#endif