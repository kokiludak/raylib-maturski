#include <raylib.h>
#include "managers/InputManager.hpp"
#include "managers/commands/PlayerCommands.hpp"
#include "managers/Physics.hpp"
#include "managers/GameManager.hpp"
#include "managers/SpawnEvent.hpp"
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
    SpawnBus::Register([&gameManager](std::unique_ptr<GameObject> obj){
        gameManager.RegisterObject(std::move(obj));
    });
    Physics physics;
    InputManager input;
    Player* player = SpawnBus::Spawn<Player>(Rectangle{100.0f, 100.0f, 50.0f, 90.0f});
    player->collider = {
        LAYER_PLAYER,
        LAYER_ENEMY | LAYER_WALL
    };

    MachineGun mg(5,0.15f, 300.0f);
    player->weapon = &mg;


    MoveLeft moveLeft(player);
    MoveRight moveRight(player);
    Stop stop(player);
    Fire fire(player);

    
    input.setLeft(&moveLeft);
    input.setRight(&moveRight);
    input.setStop(&stop);
    input.setFire(&fire);

    CollisionBody* testWall = SpawnBus::Spawn<CollisionBody>();
    testWall->SetTransform({1200, 600, 1200, 100});
    testWall->SetCenter({600, 600});
    testWall->collider = {
        LAYER_WALL,
        0
    };
    
    physics.SetBounds(200, 1400);
    physics.RegisterBody(player);
    physics.RegisterCollider(testWall);

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        std::vector<Command*> inputs = input.handleInput();
        for(Command* c : inputs){
            c->execute();
        }
        gameManager.Update(delta);
        physics.Update(delta);


        BeginDrawing();
        ClearBackground(BLACK);
        gameManager.Render();
        DrawRectangle(testWall->GetPosition().x, 
            testWall->GetPosition().y,
            testWall->GetTransform().width, testWall->GetTransform().height,
            BLUE
            );

        

        //Debug info
        Vector2 mousePos = GetMousePosition();
        DrawText(TextFormat("Player pos: %d %d", (int)player->GetPosition().x, (int)player->GetPosition().y), 10, 30, 10, RAYWHITE);
        DrawText(player->Collides(testWall) ? "collide" : "ne collide", 10, 50, 10, RAYWHITE);

        DrawText(TextFormat("Grounded: %s", player->isGrounded ? "yes\n" : "no\n"), 10, 70, 10, RAYWHITE);
        DrawText(TextFormat("Mouse pos: %d %d", (int)mousePos.x, (int)mousePos.y), 10, 90, 10, RAYWHITE);

        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
}