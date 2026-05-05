#include <raylib.h>
#include "managers/InputManager.hpp"
#include "managers/commands/PlayerCommands.hpp"
#include "managers/Physics.hpp"
#include "managers/GameManager.hpp"
#include "objects/Player.hpp"
#include "objects/Collision.hpp"
#include "objects/CollisionBody.hpp"
#include "objects/weapons/MachineGun.hpp"
#define SCREEN_HEIGHT 1600
#define SCREEN_WIDTH 1600
#define TARGET_FPS 120


#include <iostream>

int main() 
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    GameManager gameManager;
    GameObject::manager = &gameManager;

    Player* player = GameObject::Instantiate<Player>(Rectangle{100.0f, 100.0f, 100.0f, 100.0f});
    player->collider = {
        LAYER_PLAYER,
        LAYER_ENEMY | LAYER_WALL
    };

    MachineGun mg(5, 300.0f, 0.15f);
    player->weapon = &mg;


    MoveLeft moveLeft(player);
    MoveRight moveRight(player);
    Stop stop(player);
    Fire fire(player);

    InputManager input;
    input.setLeft(&moveLeft);
    input.setRight(&moveRight);
    input.setStop(&stop);
    input.setFire(&fire);

    CollisionBody* testWall = GameObject::Instantiate<CollisionBody>();
    testWall->SetTransform({1200, 600, 1200, 100});
    testWall->SetCenter({600, 600});
    testWall->collider = {
        LAYER_WALL,
        0
    };



    Physics physics;
    physics.RegisterBody(player);
    physics.RegisterCollider(testWall);

    std::cout << "i am start man\n";
    std::cout << "i am sigma man\n";
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        std::vector<Command*> inputs = input.handleInput();
        for(Command* c : inputs){
            c->execute();
        }
        if(IsKeyPressed(KEY_R)) player->SetPosition({100, 100});
        

        gameManager.Update(delta);
        //player->Update(delta);
        physics.Update(delta);
        BeginDrawing();
        ClearBackground(BLACK);


        gameManager.Render();
        DrawRectangle(testWall->GetPosition().x, 
            testWall->GetPosition().y,
            testWall->GetTransform().width, testWall->GetTransform().height,
            BLUE
            );

        //Debug information
        DrawText(TextFormat("Player pos: %d %d", (int)player->GetPosition().x, (int)player->GetPosition().y), 10, 30, 10, RAYWHITE);
        DrawText(player->Collides(testWall) ? "collide" : "ne collide", 10, 50, 10, RAYWHITE);

        DrawText(TextFormat("Grounded: %s", player->isGrounded ? "yes\n" : "no\n"), 10, 70, 10, RAYWHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
}