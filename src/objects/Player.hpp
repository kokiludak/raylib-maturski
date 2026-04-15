#pragma once
#include "RigidBody.hpp"

class Player : public RigidBody {
public:
    Player(Vector2 pos);
    //void PreUpdate(float deltaTime) override;
    //void PostUpdate(float deltaTime) override;
    void MoveLeft();
    void MoveRight();
    void Stop();
private:
    int hp;
};