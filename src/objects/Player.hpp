#pragma once
#include "RigidBody.hpp"
#include "weapons/Weapon.hpp"
class Player : public RigidBody {
public:
    Player(Vector2 pos);
    Player(Rectangle transform);
    void Update(float deltaTime) override;
    void MoveLeft();
    void MoveRight();
    void Fire();
    void Stop();
private:
    Vector2 desiredMovement;
    Weapon* weapon;
    int hp;
};