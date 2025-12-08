#ifndef BALL_H
#define BALL_H

#include "../game_engine/engine.h"

class Vec2{
    public:
        Vec2()
            : x(0.0f), y(0.0f)
        {}

        Vec2(float x, float y)
            : x(x), y(y)
        {}

        Vec2 operator+(Vec2 const& rhs){
            return Vec2(x + rhs.x, y + rhs.y);
        }

        Vec2& operator+=(Vec2 const& rhs){
            x += rhs.x;
            y += rhs.y;

            return *this;
        }

        Vec2 operator*(float rhs){
            return Vec2(x * rhs, y * rhs);
        }

        float x, y;
};

class Ball{
    public:

        Ball();

        Ball(Vec2 position)
            : position(position)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = BALL_WIDTH;
            rect.h = BALL_HEIGHT;
        }

        void Draw(SDL_Renderer* renderer){
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        int get_b_h() const{
            return BALL_HEIGHT;
        }

        int get_b_w() const{
            return BALL_WIDTH;
        }

        void setPosition(Vec2 pos){
            position = pos;
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
        }

        Vec2 position;
        SDL_Rect rect{};

        const int BALL_WIDTH = 15;
        const int BALL_HEIGHT = 15;

};

class Paddle{
    public:
        Paddle(Vec2 position)
            : position(position)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = PADDLE_WIDTH;
            rect.h = PADDLE_HEIGHT;
        }

        void Draw(SDL_Renderer* renderer){
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        void setPosition(Vec2 pos){
            position = pos;
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
        }

        Vec2 position;
        SDL_Rect rect{};

        const int PADDLE_WIDTH = 10;
        const int PADDLE_HEIGHT = 80;
};

class PlayerScore{
    public:
        PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
            : renderer(renderer), font(font)
        {
            surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            int width, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = width;
            rect.h = height;
        }

        ~PlayerScore(){
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void Draw(){
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }

        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Surface* surface{};
        SDL_Texture* texture{};
        SDL_Rect rect{};
};

#endif