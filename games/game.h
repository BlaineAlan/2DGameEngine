#ifndef GAME_H
#define GAME_H

#include "../game_engine/engine.h"

class MyGame : public IGame {
    public:

        SDL_Color bg = {0, 0, 0, 255};
        SDL_Rect playerRect;

        void loadMedia(SDL_Renderer* renderer) override;
        
        void render(SDL_Renderer* renderer) override;

};

#endif