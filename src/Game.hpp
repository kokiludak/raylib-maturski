#pragma once
#include <raylib.h>

#include "managers/Physics.hpp"
#include "managers/GameManager.hpp"
#include "managers/InputManager.hpp"
#include "World.hpp"
#include "objects/Player.hpp"
#include "managers/commands/PlayerCommands.hpp"


class Game {
public:
    Game();
    void Loop();
private:
    Camera2D camera {};
    Physics physics;
    GameManager gameManager;
    InputManager input;
    World world;
    MoveLeft moveLeft;
    MoveRight moveRight;
    Stop stop;
    Fire fire;

    Player* player = nullptr;
    float accumulator = 0.0f;

    CollisionBody* wall;
};