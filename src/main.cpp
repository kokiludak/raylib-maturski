#include <raylib.h>
#include "managers/InputManager.hpp"
#include "managers/commands/PlayerCommands.hpp"
#include "objects/Player.hpp"
#define SCREEN_HEIGHT 1600
#define SCREEN_WIDTH 900
#define TARGET_FPS 120


int main() 
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    
    
    Player player({0.0f, 0.0f});
    MoveLeft moveLeft(&player);
    MoveRight moveRight(&player);
    Stop stop(&player);

    InputManager input;
    input.setLeft(&moveLeft);
    input.setRight(&moveRight);
    input.setStop(&stop);
    while (!WindowShouldClose())
    {

        std::vector<Command*> inputs = input.handleInput();
        for(Command* c : inputs){
            c->execute();
        }
        player.Update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(player.GetPosition().x, player.GetPosition().y, 100, 100, RAYWHITE);
        EndDrawing();
    }
    
    CloseWindow();
}