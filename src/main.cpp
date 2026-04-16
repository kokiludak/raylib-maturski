#include <raylib.h>
#include "managers/InputManager.hpp"
#include "managers/commands/PlayerCommands.hpp"
#include "managers/PhysicsHandler.hpp"
#include "objects/Player.hpp"
#include "objects/Collision.hpp"
#include "objects/CollisionBody.hpp"
#define SCREEN_HEIGHT 1600
#define SCREEN_WIDTH 900
#define TARGET_FPS 120


#include <iostream>

int main() 
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    
    
    Player player({100.0f, 100.0f});
    player.collider = {
        {0, 0, 100, 100},
        LAYER_PLAYER,
        LAYER_ENEMY | LAYER_WALL
    };

    MoveLeft moveLeft(&player);
    MoveRight moveRight(&player);
    Stop stop(&player);

    InputManager input;
    input.setLeft(&moveLeft);
    input.setRight(&moveRight);
    input.setStop(&stop);


    CollisionBody testWall;
    testWall.SetPosition({600, 600});

    std::cout << "position: " << testWall.GetPosition().x << ' ' << testWall.GetPosition().y << '\n';
    testWall.collider = {
        {0, 0, 1200, 100},
        LAYER_WALL,
        0
    };
    std::cout << "height width " << testWall.collider.area.height << ' ' << testWall.collider.area.width << '\n';

    PhysicsHandler physicsHandler;
    physicsHandler.RegisterBody(&player);
    physicsHandler.RegisterCollider(&testWall);
    while (!WindowShouldClose())
    {

        std::vector<Command*> inputs = input.handleInput();
        for(Command* c : inputs){
            c->execute();
        }
        float delta = GetFrameTime();
        player.Update(delta);
        physicsHandler.Update(delta);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(player.GetPosition().x - 50, player.GetPosition().y - 50, 100, 100, RAYWHITE);
        DrawRectangle(testWall.GetPosition().x - testWall.collider.area.width/2, 
            testWall.GetPosition().y - testWall.collider.area.height/2,
            testWall.collider.area.width, testWall.collider.area.height,
            ORANGE
            );

        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
}