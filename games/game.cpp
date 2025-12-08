
#include "game.h"
#include "../game_engine/engine.h"
#include "ball.h"

//Set everything to just be at 0
MyGame::MyGame(Engine& engine)
    :  ball(Vec2(0.0f, 0.0f)), paddle1(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f)), paddle2(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f))
{}

void MyGame::init(Engine& engine){
    float w = engine.get_screen_w();
    float h = engine.get_screen_h();
    
    //set ball to be in the middle of the screen
    ball.setPosition(
        Vec2(
            (w / 2.0f) - (ball.get_b_w() / 2.0f),
            (h / 2.0f) - (ball.get_b_w() / 2.0f)
        )
    );

    //set paddles to start at the middle of the left and right side
    paddle1.setPosition(
        Vec2(50.0f, SCREEN_HEIGHT / 2.0f),
        Vec2(0.0f, 0.0f)
    );

    paddle2.setPosition(
        Vec2(SCREEN_WIDTH - 50.0f, SCREEN_HEIGHT / 2.0f),
        Vec2(0.0f, 0.0f)
    );

}

void MyGame::update(float dt){

    //check if paddle 1 is moving up or down or not moving at all, and adjust it's velocity accordingly
    if(buttons[Buttons::PaddleOneUp]){
        paddle1.velocity.y = -PADDLE_SPEED;
    }else if(buttons[Buttons::PaddleOneDown]){
        paddle1.velocity.y = PADDLE_SPEED;
    }else{
        paddle1.velocity.y = 0.0f;
    }
    //check if paddle 2 is moving up or down or not moving at all, and adjust it's velocity accordingly
    if(buttons[Buttons::PaddleTwoUp]){
        paddle2.velocity.y = -PADDLE_SPEED;
    }else if(buttons[Buttons::PaddleTwoDown]){
        paddle2.velocity.y = PADDLE_SPEED;
    }else{
        paddle2.velocity.y = 0.0f;
    }

    //call the paddle update functions to find their new positions on the screen given the dt
    paddle1.Update(dt);
    paddle2.Update(dt);
}

void MyGame::handleEvent(const SDL_Event& event){
    //If a key is pressed down, check if it's a player 1 or 2 movement up or down and set those to true in the array
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_w){
            buttons[Buttons::PaddleOneUp] = true;
        }else if(event.key.keysym.sym == SDLK_s){
            buttons[Buttons::PaddleOneDown] = true;
        }else if(event.key.keysym.sym == SDLK_UP){
            buttons[Buttons::PaddleTwoUp] = true;
        }else if(event.key.keysym.sym == SDLK_DOWN){
            buttons[Buttons::PaddleTwoDown] = true;
        }
    //If a key was pressed down but is now pressed up, check if it's a player 1 or 2 movement key and set those to false
    }else if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_w){
            buttons[Buttons::PaddleOneUp] = false;
        }else if(event.key.keysym.sym == SDLK_s){
            buttons[Buttons::PaddleOneDown] = false;
        }else if(event.key.keysym.sym == SDLK_UP){
            buttons[Buttons::PaddleTwoUp] = false;
        }else if(event.key.keysym.sym == SDLK_DOWN){
            buttons[Buttons::PaddleTwoDown] = false;
        }
    }
}

//not used right now for pong
void MyGame::loadMedia(SDL_Renderer* renderer) {
    // Just an example: fill rect for now
    playerRect = {100, 100, 64, 64};
}

void MyGame::render(SDL_Renderer* renderer) {
    //initialize our TTF (text)
    TTF_Init();
    //set the font
    TTF_Font* scoreFont = TTF_OpenFont("fonts/ttf/DejaVuSansMono.ttf", 40);
    //Set where the player 1 text will go
    PlayerScore playerOneScoreText(Vec2(SCREEN_WIDTH / 4, 20), renderer, scoreFont);
    //Set where the player 2 text will go
    PlayerScore playerTwoScoreText(Vec2(3 * SCREEN_WIDTH / 4, 20), renderer, scoreFont);

    //set the draw color to black to draw the background
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);
    //then set the draw color to white for everything else
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //draw the white dashed-line down the center of the screen
    for(int y = 0; y < get_screen_h(); y++){
        if(y % 5){
            SDL_RenderDrawPoint(renderer, get_screen_w() / 2, y);
        }
    }

    //draw the ball
    ball.Draw(renderer);
    //draw the paddles
    paddle1.Draw(renderer);
    paddle2.Draw(renderer);
    //draw the score text
    playerOneScoreText.Draw();
    playerTwoScoreText.Draw();

}

int MyGame::get_screen_h() const{
    return SCREEN_HEIGHT;
}

int MyGame::get_screen_w() const{
    return SCREEN_WIDTH;
}
