/**
 * @file game.h
 * @author Blaine Cochensparger 
 * @brief Header file for the game Pong. Includes the MyGame class, which is a child of IGame from the engine.
 * 
 */

#ifndef GAME_H
#define GAME_H

#include "../game_engine/engine.h"
#include "ball.h"

class MyGame : public IGame {
    public:
        SDL_Color bg = {0, 0, 0, 255};
        SDL_Rect playerRect;

        /**
         * @brief Construct a new MyGame object
         * 
         * @param engine 
         */
        MyGame(Engine& engine);

        /**
         * @brief Initialize the game using the engine, setting everything in it's initial place
         * 
         * @param engine 
         */
        void init(Engine& engine) override;

        /**
         * @brief Load any necessary media using the engine's renderer
         * 
         * @param renderer 
         */
        void loadMedia(SDL_Renderer* renderer) override;
        
        /**
         * @brief Render everything to the screen at the correct position
         * 
         * @param renderer 
         */
        void render(SDL_Renderer* renderer) override;

        /**
         * @brief Handles user input, reading what keys they're pressing and making sure the correct paddle is assigned to move up or down
         * 
         * @param event 
         */
        void handleEvent(const SDL_Event& event) override;

        /**
         * @brief Update the current game, including the ball movement and paddle movement
         * 
         * @param dt 
         */
        void update(float dt) override;

        /**
         * @brief Get the SCREEN_HEIGHT object
         * 
         * @return int 
         */
        int get_screen_h() const;

        /**
         * @brief Get the SCREEN_WIDTH object
         * 
         * @return int 
         */
        int get_screen_w() const;

    private:
        //once again setting screen height because I haven't decided if this is something that should be set by the engine or the game lol
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;

        //This game contains a ball and two paddles
        Ball ball;

        Paddle paddle1;

        Paddle paddle2;

        //Lays out what paddle movements there are, obviously just up and down, no left and right. Starts at 0 for the array
        enum Buttons{
            PaddleOneUp = 0,
            PaddleOneDown,
            PaddleTwoUp,
            PaddleTwoDown,
        };

        //array of bools to tell us which movements are done by which player
        bool buttons[4] = {};

        //sets a constant paddle speed 
        const float PADDLE_SPEED = 1.0f;

};

#endif