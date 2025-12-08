# 2DGameEngine

The goal with this project is to create a 2D game engine that can be used to create simple 2D games. 

1. First make the engine

2. Make Pong with it for a demo

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

So far the demo can open a window and draw out all the objects needed for the game 'Pong', and both paddles can move. Use the up and down arrow keys for the right side, and w and s keys for the left side. All the files are seperated into engine files and game files, to avoid hardcoding anything game specific into the engine itself.
