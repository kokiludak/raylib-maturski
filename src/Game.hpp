#pragma once
#include <raylib.h>

#include "managers/Physics.hpp"
#include "managers/GameManager.hpp"
#include "managers/InputManager.hpp"
#include "objects/Player.hpp"
#include "managers/commands/PlayerCommands.hpp"

/*
class MoveLeft;
class MoveRight;
class Stop;
class Fire;
*/

class Game {
public:
    Game();
    void Loop();
private:
    Camera2D camera {};
    Physics physics;
    GameManager gameManager;
    InputManager input;
    MoveLeft moveLeft;
    MoveRight moveRight;
    Stop stop;
    Fire fire;


    Player* player = nullptr;
    std::vector<CollisionBody*> testWalls;
    float accumulator = 0.0f;
};