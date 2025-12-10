
#include "game.h"
#include "../game_engine/engine.h"
#include "ball.h"
#include <SDL2/SDL_mixer.h>

///BUG, IF YOU HOLD DOWN WHEN THE GAME ENDS AND START A NEW GAME YOULL BE GOING DOWN FOREVER, SHOULD PROBABLY RESET POSITION AND MOVMENT WHENN A NEW GAME STARTS

//Set everything to just be at 0
MyGame::MyGame(Engine& engine)
    :  ball(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f)), paddle1(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f)), paddle2(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f))
{}

MyGame::~MyGame(){
    Mix_FreeChunk(wallHitSound);
    Mix_FreeChunk(paddleHitSound);
}


void MyGame::init(Engine& engine){
    float w = engine.get_screen_w();
    float h = engine.get_screen_h();

    renderer = engine.get_renderer();

    //initialize our TTF (text)
    TTF_Init();
    //set the font
    font = TTF_OpenFont("fonts/ttf/DejaVuSansMono.ttf", 40);
    
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << "\n";
    }

    wallHitSound = Mix_LoadWAV("sounds/wallHitSound.wav");

    if (!wallHitSound) {
        std::cout << "Failed to load wallHitSound.wav: " << Mix_GetError() << "\n";
    }

    paddleHitSound = Mix_LoadWAV("sounds/paddleHitSound.wav");
    if (!paddleHitSound) {
        std::cout << "Failed to load paddleHitSound.wav: " << Mix_GetError() << "\n";
    }

    //set ball to be in the middle of the screen
    ball.setPosition(
        Vec2((w / 2.0f),(h / 2.0f)),
        Vec2(BALL_SPEED, 0.0f)
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


    playerOneScoreText.Init(Vec2(SCREEN_WIDTH / 4, 20), renderer, font, "");
    playerTwoScoreText.Init(Vec2(3 * SCREEN_WIDTH / 4, 20), renderer, font, "");

    menuText.Init(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40), renderer, font, "PONG - First to 10 wins");

    pressEnterText.Init(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20), renderer, font, "Press ENTER");

    gameOverText.Init(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40), renderer, font, "GAME OVER");



}

void MyGame::update(float dt){

    switch(state){
        case GameState::Menu:
            break;
        case GameState::Playing:
            UpdateGameplay(dt);
            break;
        case GameState::GameOver:
            return;
    }

}

void MyGame::handleEvent(const SDL_Event& event){
    if(state == GameState::Menu){
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
            ResetGame();
            state = GameState::Playing;
        }
        return;
    }
    if(state == GameState::GameOver){
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
            state = GameState::Menu;
        }
        return;
    }

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
    //set the draw color to black to draw the background
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);
    
    if(state == GameState::Menu){
        menuText.Draw();
        pressEnterText.Draw();
        return;
    }

    if(state == GameState::GameOver){
        gameOverText.Draw();
        pressEnterText.Draw();
        return;
    }
    
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

Contact MyGame::CheckPaddleCollision(Ball const& ball, Paddle const& paddle){
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + ball.get_b_w();
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + ball.get_b_h();

    float paddleLeft = paddle.position.x;
    float paddleRight = paddle.position.x + paddle.PADDLE_WIDTH;
    float paddleTop = paddle.position.y;
    float paddleBottom = paddle.position.y + paddle.PADDLE_HEIGHT;

    Contact contact{};

    if(ballLeft >= paddleRight){
        return contact;
    }
    if(ballRight <= paddleLeft){
        return contact;
    }
    if(ballTop >= paddleBottom){
        return contact;
    }
    if(ballBottom <= paddleTop){
        return contact;
    }
    
    float paddleRangeUpper = paddleBottom - (2.0f * paddle.PADDLE_HEIGHT / 3.0f);
    float paddleRangeMiddle = paddleBottom - (paddle.PADDLE_HEIGHT / 3.0f);

    if(ball.velocity.x < 0){
        contact.penetration = paddleRight - ballLeft;
    }else if(ball.velocity.x > 0){
        contact.penetration = paddleLeft - ballRight;
    }

    if((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper)){
        contact.type = CollisionType::Top;
    }else if((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle)){
        contact.type = CollisionType::Middle;
    }else{
        contact.type = CollisionType::Bottom;
    }

    return contact;
}

Contact MyGame::CheckWallCollision(Ball const& ball){
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + ball.get_b_w();
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + ball.get_b_h();

    Contact contact{};

    if(ballLeft < 0.0f){
        contact.type = CollisionType::Left;
    }else if(ballRight > SCREEN_WIDTH){
        contact.type = CollisionType::Right;
    }else if(ballTop < 0.0f){
        contact.type = CollisionType::Top;
        contact.penetration = -ballTop;
    }else if(ballBottom > SCREEN_HEIGHT){
        contact.type = CollisionType::Bottom;
        contact.penetration = SCREEN_HEIGHT - ballBottom;
    }

    return contact;
}

void MyGame::ResetGame(){
    playerOneScore = 0;
    playerTwoScore = 0;

    playerOneScoreText.setScore(0);
    playerTwoScoreText.setScore(0);

    ResetBall();
}

void MyGame::ResetBall(bool slow){
    float dir = (lastPointLoser == 1) ? -1.0f : 1.0f;
    float speed = BALL_SPEED * (slow ? SLOW_MULTIPLIER : 1.0f);
    serveIsSlow = slow;

    ball.setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vec2(dir * speed, 0.0f));
}

void MyGame::UpdateGameplay(float dt){
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

    ball.Update(dt);

    if(Contact contact = CheckPaddleCollision(ball, paddle1); contact.type != CollisionType::None){
        ball.CollideWithPaddle(contact);

        Mix_PlayChannel(-1, paddleHitSound, 0);

        if(serveIsSlow){
            float sign = (ball.velocity.x < 0) ? -1.0f : 1.0f;
            ball.velocity.x = sign * BALL_SPEED;
            serveIsSlow = false;
        }
    }else if(contact = CheckPaddleCollision(ball, paddle2); contact.type != CollisionType::None){
        ball.CollideWithPaddle(contact);

        Mix_PlayChannel(-1, paddleHitSound, 0);

        if(serveIsSlow){
            float sign = (ball.velocity.x < 0) ? -1.0f : 1.0f;
            ball.velocity.x = sign * BALL_SPEED;
            serveIsSlow = false;
        }
    }else if(contact = CheckWallCollision(ball); contact.type != CollisionType::None){
        ball.CollideWithWall(contact);

        if(contact.type == CollisionType::Left){
            ++playerTwoScore;

            playerTwoScoreText.setScore(playerTwoScore);

            lastPointLoser = 1;

            ResetBall(true);


        }else if(contact.type == CollisionType::Right){
            ++playerOneScore;

            playerOneScoreText.setScore(playerOneScore);

            lastPointLoser = 2;

            ResetBall(true);

        }else{
            Mix_PlayChannel(-1, wallHitSound, 0);
        }

        if(playerOneScore >= WIN_SCORE){
            gameOverText.setText("Player 1 wins!");
            state = GameState::GameOver;
        }else if(playerTwoScore >= WIN_SCORE){
            gameOverText.setText("Player 2 wins!");
            state = GameState::GameOver;
        }
    }
}
