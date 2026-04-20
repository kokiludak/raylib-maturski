#include <raylib.h>
#include "managers/InputManager.hpp"
#include "managers/commands/PlayerCommands.hpp"
#include "managers/PhysicsHandler.hpp"
#include "objects/Player.hpp"
#include "objects/Collision.hpp"
#include "objects/CollisionBody.hpp"
#define SCREEN_HEIGHT 1600
#define SCREEN_WIDTH 1600
#define TARGET_FPS 120


#include <iostream>

int main() 
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    
    
    Player player({100.0f, 100.0f, 100.0f, 100.0f});
    player.collider = {
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
    testWall.SetTransform({1200, 600, 1200, 100});
    testWall.SetCenter({1200, 600});
    testWall.collider = {
        LAYER_WALL,
        0
    };
    PhysicsHandler physicsHandler;
    physicsHandler.RegisterBody(&player);
    physicsHandler.RegisterCollider(&testWall);
    while (!WindowShouldClose())
    {

        std::vector<Command*> inputs = input.handleInput();
        for(Command* c : inputs){
            c->execute();
        }
        if(IsKeyPressed(KEY_R)) player.SetPosition({100, 100});
        float delta = GetFrameTime();
        player.Update(delta);
        physicsHandler.Update(delta);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(player.GetPosition().x, player.GetPosition().y, 100, 100, RAYWHITE);
        DrawRectangle(testWall.GetPosition().x, 
            testWall.GetPosition().y,
            testWall.GetTransform().width, testWall.GetTransform().height,
            ORANGE
            );

        //Debug information
        DrawText(TextFormat("Player pos: %d %d", (int)player.GetPosition().x, (int)player.GetPosition().y), 10, 30, 10, RAYWHITE);
        DrawText(player.Collides(&testWall) ? "collide" : "ne collide", 10, 50, 10, RAYWHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
}