/**
 * @file ball.h
 * @author Blaine Cochensparger
 * @brief Header file for the Pong game objects, including Vec2, Ball, Paddles, and Score Text
 * 
 */

#ifndef BALL_H
#define BALL_H

#include "../game_engine/engine.h"

class Vec2{
    public:
        /**
         * @brief Construct a new Vec2 object with default positions
         * 
         */
        Vec2()
            : x(0.0f), y(0.0f)
        {}

        /**
         * @brief Construct a new Vec2 object
         * 
         * @param x 
         * @param y 
         */
        Vec2(float x, float y)
            : x(x), y(y)
        {}

        /**
         * @brief + two Vec2 objects
         * 
         * @param rhs 
         * @return Vec2 
         */
        Vec2 operator+(Vec2 const& rhs){
            return Vec2(x + rhs.x, y + rhs.y);
        }

        /**
         * @brief += two Vec2 objects
         * 
         * @param rhs 
         * @return Vec2& 
         */
        Vec2& operator+=(Vec2 const& rhs){
            x += rhs.x;
            y += rhs.y;

            return *this;
        }

        /**
         * @brief * two Vec2 objects
         * 
         * @param rhs 
         * @return Vec2 
         */
        Vec2 operator*(float rhs){
            return Vec2(x * rhs, y * rhs);
        }

        float x, y;
};

class Ball{
    public:
        
        /**
         * @brief Construct a new Ball object
         * 
         */
        Ball();

        /**
         * @brief Construct a new Ball object with a given position
         * 
         * @param position 
         */
        Ball(Vec2 position)
            : position(position)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = BALL_WIDTH;
            rect.h = BALL_HEIGHT;
        }

        /**
         * @brief Draw the ball where it's meant to be
         * 
         * @param renderer 
         */
        void Draw(SDL_Renderer* renderer){
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }
        
        /**
         * @brief Get the BALL_HEIGHT object
         * 
         * @return int 
         */
        int get_b_h() const{
            return BALL_HEIGHT;
        }

        /**
         * @brief Get the BALL_WIDTH object
         * 
         * @return int 
         */
        int get_b_w() const{
            return BALL_WIDTH;
        }

        /**
         * @brief Set the position object given a position
         * 
         * @param pos 
         */
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

        /**
         * @brief Construct a new Paddle object given a position and velocity
         * 
         * @param position 
         * @param velocity 
         */
        Paddle(Vec2 position, Vec2 velocity)
            : position(position), velocity(velocity)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = PADDLE_WIDTH;
            rect.h = PADDLE_HEIGHT;
        }

        /**
         * @brief Update where the paddle is meant to be given a dt
         * 
         * @param dt 
         */
        void Update(float dt){
            position += velocity * dt;

            if(position.y < 0){
                position.y = 0;
            }else if(position.y > (720 - PADDLE_HEIGHT)){
                position.y = 720 - PADDLE_HEIGHT;
            }
        }

        /**
         * @brief Draw the paddle according to it's position
         * 
         * @param renderer 
         */
        void Draw(SDL_Renderer* renderer){
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        /**
         * @brief Set the position and velocity object given a position and velocity
         * 
         * @param pos 
         * @param vel 
         */
        void setPosition(Vec2 pos, Vec2 vel){
            position = pos;
            velocity = vel;
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
        }

        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};

        const int PADDLE_WIDTH = 10;
        const int PADDLE_HEIGHT = 80;
};

class PlayerScore{
    public:

        /**
         * @brief Construct a new PlayerScore object
         * 
         * @param position 
         * @param renderer 
         * @param font 
         */
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

        /**
         * @brief Destroy the PlayerScore object
         * 
         */
        ~PlayerScore(){
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        /**
         * @brief Draw where they are meant to be 
         * 
         */
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