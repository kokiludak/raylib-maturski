#include "Game.hpp"
#include "managers/SpawnEvent.hpp"
#include "objects/Player.hpp"
#include "objects/enemies/Slime.hpp"
#include "objects/Collision.hpp"
#include "objects/CollisionBody.hpp"
#include "objects/weapons/MachineGun.hpp"
#include "objects/structures/Platform.hpp"

#include <iostream>
constexpr int SCREEN_HEIGHT = 1600;
constexpr int SCREEN_WIDTH  = 1600;
constexpr int TARGET_FPS = 120;
constexpr float MIN_WORLD_BOUND = 200.0f, MAX_WORLD_BOUND = 1300.0f;

Game::Game() : physics(), gameManager(physics), input(), world(MIN_WORLD_BOUND, MAX_WORLD_BOUND) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.offset = { 0, SCREEN_HEIGHT / 2.0f };

    
    SpawnBus::Register([this](std::unique_ptr<GameObject> obj) {
        gameManager.RegisterObject(std::move(obj));
    });

    player = SpawnBus::Spawn<Player>(Rectangle{MIN_WORLD_BOUND + 100.0f, 100.0f, 50.0f, 90.0f});
    world.Init(player);


    Platform* wall = SpawnBus::Spawn<Platform>(Rectangle{1200.0f, 600.0f, 600, 100});
    wall->SetCenter({600.0f, 600.0f});
    wall->collider = {
        LAYER_WALL,
        0
    };

    player->collider = {
        LAYER_PLAYER,
        LAYER_ENEMY | LAYER_WALL
    };

    
    player->weapon = new MachineGun(5, 0.15f, 300.0f);

    moveLeft = MoveLeft(player);
    moveRight = MoveRight(player);
    stop = Stop(player);
    fire = Fire(player);

    input.setLeft(&moveLeft);
    input.setRight(&moveRight);
    input.setStop(&stop);
    input.setFire(&fire);
}


void Game::Loop(){
    float delta = GetFrameTime();
    delta = std::min(delta, 0.05f);
    accumulator += delta;
    camera.target = {0, player->GetCenter().y};


    if(IsKeyPressed(KEY_Y)){
        SpawnBus::Spawn<Slime>(player, Vector2{200, 200});
    }
    std::vector<Command*> inputs = input.handleInput();
    for(Command* c : inputs){
        c->execute();
    }
    world.Update(delta);
    gameManager.Update(delta);
    while(accumulator >= 1.0 / physics.UPS){
        physics.Update(1.0 / physics.UPS);
        accumulator -= 1.0 / physics.UPS;
        
    }


    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    gameManager.Render();
    
    EndMode2D();
    DrawText("AMMO", 1500 - MeasureText("AMMO", 30)/2, 200, 30, RAYWHITE);
    for(int i = 0; i < player->weapon->GetCurrentAmmo(); i++){
        DrawRectangle(1450, 300 + 100*i, 100, 75, RAYWHITE);
    }

    DrawText("HEALTH", 200 - MeasureText("HEALTH", 30)/2, 100, 30, RAYWHITE);
    for(int i = 0; i < player->GetHealth(); i++){
        DrawRectangle(150 + 125*i, 150, 100, 50, RED);
    }
    //Debug info
    Vector2 mousePos = GetMousePosition();
    DrawText(TextFormat("Player pos: %d %d", (int)player->GetPosition().x, (int)player->GetPosition().y), 10, 30, 10, RAYWHITE);
    
    
    DrawText(TextFormat("Grounded: %s", player->isGrounded ? "yes\n" : "no\n"), 10, 70, 10, RAYWHITE);
    DrawText(TextFormat("Mouse pos: %d %d", (int)mousePos.x, (int)mousePos.y), 10, 90, 10, RAYWHITE);
    DrawFPS(10, 10);
    EndDrawing();
}

