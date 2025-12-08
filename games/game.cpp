#include "game.h"
#include "../game_engine/engine.h"
#include "ball.h"

MyGame::MyGame(Engine& engine)
    :  ball(Vec2(0.0f, 0.0f)), paddle1(Vec2(0.0f, 0.0f)), paddle2(Vec2(0.0f, 0.0f))
{}

void MyGame::init(Engine& engine){
    float w = engine.get_screen_w();
    float h = engine.get_screen_h();

    
    ball.setPosition(
        Vec2(
            (w / 2.0f) - (ball.get_b_w() / 2.0f),
            (h / 2.0f) - (ball.get_b_w() / 2.0f)
        )
    );
}


void MyGame::loadMedia(SDL_Renderer* renderer) {
    // Just an example: fill rect for now
    playerRect = {100, 100, 64, 64};
}

void MyGame::render(SDL_Renderer* renderer) {
    TTF_Init();

    TTF_Font* scoreFont = TTF_OpenFont("fonts/ttf/DejaVuSansMono.ttf", 40);

    PlayerScore playerOneScoreText(Vec2(SCREEN_WIDTH / 4, 20), renderer, scoreFont);

    PlayerScore playerTwoScoreText(Vec2(3 * SCREEN_WIDTH / 4, 20), renderer, scoreFont);


    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int y = 0; y < get_screen_h(); y++){
        if(y % 5){
            SDL_RenderDrawPoint(renderer, get_screen_w() / 2, y);
        }
    }

    ball.setPosition(
        Vec2((SCREEN_WIDTH / 2.0f) - (ball.BALL_WIDTH / 2.0f),
        (SCREEN_HEIGHT / 2.0f) - (ball.BALL_HEIGHT / 2.0f)));

    paddle1.setPosition(
        Vec2(50.0f, (SCREEN_HEIGHT / 2.0f) - (paddle1.PADDLE_HEIGHT / 2.0f))
    );

    paddle2.setPosition(
        Vec2(SCREEN_WIDTH - 50.0f, (SCREEN_HEIGHT / 2.0f) - (paddle2.PADDLE_HEIGHT / 2.0f))
    );

    ball.Draw(renderer);

    paddle1.Draw(renderer);
    paddle2.Draw(renderer);

    playerOneScoreText.Draw();
    playerTwoScoreText.Draw();

}

int MyGame::get_screen_h() const{
    return SCREEN_HEIGHT;
}

int MyGame::get_screen_w() const{
    return SCREEN_WIDTH;
}
