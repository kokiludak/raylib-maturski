#pragma once
#include "RigidBody.hpp"
#include "Player.hpp"
class Enemy : public RigidBody {
public:
    Enemy(Player* p);
private:
    Player* player;
};