#include "Game.hpp"
#include "managers/SpawnEvent.hpp"
#include "objects/Player.hpp"
#include "objects/enemies/Slime.hpp"
#include "objects/Collision.hpp"
#include "objects/CollisionBody.hpp"
#include "objects/weapons/MachineGun.hpp"
constexpr int SCREEN_HEIGHT = 1600;
constexpr int SCREEN_WIDTH  = 1600;
constexpr int TARGET_FPS = 120;

Game::Game() : physics(), gameManager(physics), input() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "g");
    SetTargetFPS(TARGET_FPS);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };

    SpawnBus::Register([this](std::unique_ptr<GameObject> obj) {
        gameManager.RegisterObject(std::move(obj));
    });

    player = SpawnBus::Spawn<Player>(Rectangle{100.0f, 100.0f, 50.0f, 90.0f});
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

    testWalls.resize(100);

    for (int i = 0; i < 100; i++) {
        testWalls[i] = SpawnBus::Spawn<CollisionBody>();
        testWalls[i]->SetTransform({1200.0f, 600.0f, 1200, 100});
        testWalls[i]->SetCenter({600.0f + 200.0f * i, 600 - 100.0f * i});
        testWalls[i]->collider = { LAYER_WALL, 0 };
    }
}


void Game::Loop(){
    float delta = GetFrameTime();
    delta = std::min(delta, 0.05f);
    accumulator += delta;
    camera.target = player->GetCenter();


    if(IsKeyPressed(KEY_Y)){
        SpawnBus::Spawn<Slime>(player, Vector2{200, 200});
        //slime->SetCenter({200, 200});
    }
    std::vector<Command*> inputs = input.handleInput();
    for(Command* c : inputs){
        c->execute();
    }
    gameManager.Update(delta);

    while(accumulator >= 1.0 / physics.UPS){
        physics.Update(1.0 / physics.UPS);
        accumulator -= 1.0 / physics.UPS;
        
    }
    


    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    gameManager.Render();

    for(int i  = 0; i < 100; i++){
        DrawRectangle(testWalls[i]->GetPosition().x, 
            testWalls[i]->GetPosition().y,
            testWalls[i]->GetTransform().width, testWalls[i]->GetTransform().height,
            BLUE
            );
    }
    
    EndMode2D();
    //Debug info
    Vector2 mousePos = GetMousePosition();
    DrawText(TextFormat("Player pos: %d %d", (int)player->GetPosition().x, (int)player->GetPosition().y), 10, 30, 10, RAYWHITE);
    //DrawText(player->Collides(testWall) ? "collide" : "ne collide", 10, 50, 10, RAYWHITE);

    DrawText(TextFormat("Grounded: %s", player->isGrounded ? "yes\n" : "no\n"), 10, 70, 10, RAYWHITE);
    DrawText(TextFormat("Mouse pos: %d %d", (int)mousePos.x, (int)mousePos.y), 10, 90, 10, RAYWHITE);
    DrawRectangle(200, 200, 50.0f * 8, 90.0f * 8, ColorAlpha(RAYWHITE, 0.8f));
    DrawFPS(10, 10);
    EndDrawing();
}