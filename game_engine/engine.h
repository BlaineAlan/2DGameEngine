/**
 * @file engine.h
 * @author Blaine Cochensparger
 * @brief header file for my 2D game engine. Includes the IGame class, which is a template for a game, and the Engine class which is the engine itself.
 * 
 */

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
        virtual void handleEvent(const SDL_Event& event) = 0;
        virtual void update(float dt) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
};

class Engine{
    public:
        /**
         * @brief Construct a new Engine object
         * 
         */
        Engine();

        /**
         * @brief Destroy the Engine object
         * 
         */
        ~Engine();

        /**
         * @brief initializes the game environment, creating a window and initializing the necessary SDL components. Takes a title to make the name of the window
         * 
         * @param title 
         * @return true 
         * @return false 
         */
        bool init(const char* title);

        /**
         * @brief Holds the main loop for the game
         * 
         * @param game 
         */
        void run(IGame* game);

        /**
         * @brief loadSurface function
         * 
         * @param path 
         * @return SDL_Surface* 
         */
        SDL_Surface* loadSurface( std::string path );

        /**
         * @brief loadTexture function
         * 
         * @param path 
         * @return SDL_Texture* 
         */
        SDL_Texture* loadTexture(std::string path);

        /**
         * @brief Get the SCREEN_HEIGHT object
         * 
         * @return int 
         */
        int get_screen_h() const{
            return SCREEN_HEIGHT;
        }
        
        /**
         * @brief Get the SCREEN_WIDTH object
         * 
         * @return int 
         */
        int get_screen_w() const{
            return SCREEN_WIDTH;
        }

        SDL_Renderer* get_renderer();

    private:

        //default screen height, 1280 x 720
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;
        
        //Basic keyboard presses        
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