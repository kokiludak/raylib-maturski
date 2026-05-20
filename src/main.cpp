#include <raylib.h>
#include <iostream>

#include "Game.hpp"
int main() 
{
    
    Game game;
    
    while (!WindowShouldClose())
    {
        game.Loop();
    }
    CloseWindow();
}