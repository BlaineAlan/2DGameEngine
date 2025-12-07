#include "game.h"


void MyGame::loadMedia(SDL_Renderer* renderer) {
    // Just an example: fill rect for now
    playerRect = {100, 100, 64, 64};
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}