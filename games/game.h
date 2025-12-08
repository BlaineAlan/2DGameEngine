#ifndef GAME_H
#define GAME_H

#include "../game_engine/engine.h"
#include "ball.h"

class MyGame : public IGame {
    public:
        SDL_Color bg = {0, 0, 0, 255};
        SDL_Rect playerRect;

        MyGame(Engine& engine);

        void init(Engine& engine) override;

        void loadMedia(SDL_Renderer* renderer) override;
        
        void render(SDL_Renderer* renderer) override;

        int get_screen_h() const;

        int get_screen_w() const;

    private:
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;

        Ball ball;

        Paddle paddle1;

        Paddle paddle2;
};

#endif