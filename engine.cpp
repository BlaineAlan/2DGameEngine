#include <SDL2/SDL.h>

int main(){
 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("win", 100, 100, 1000, 500, 0);

    SDL_Delay(10000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

