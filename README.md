# 2DGameEngine

The goal with this project is to create a 2D game engine that can be used to create simple 2D games. 

1. First make the engine

2. Make Pong with it for a demo

3. Continue to expand the engine and maybe make a platformer

Heres the website I'm using to learn SDL2:

https://lazyfoo.net/tutorials/SDL/index.php#Key%20Presses

And the website I'm using to recreate Pong:

https://austinmorlan.com/posts/pong_clone/


# Running

Make sure you have SDL2 installed, then

    make all

Compiles all necessary .cpp files and creates an executable called 'game'

    ./game

Runs the program

# Progress

The Pong demo is now complete. Player 1 (left) uses W + S to move, Player 2 (right) uses up + down arrow keys to move. When one person scores, the ball is served to the other person, and that is repeated until someone reaches 10, at which point the game is over and the winner is announced.
