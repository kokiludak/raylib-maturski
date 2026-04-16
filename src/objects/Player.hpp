#pragma once
#include "RigidBody.hpp"

class Player : public RigidBody {
public:
    Player(Vector2 pos);
    void Update(float deltaTime) override;
    void MoveLeft();
    void MoveRight();
    void Stop();
private:
    Vector2 desiredMovement;
    int hp;
};