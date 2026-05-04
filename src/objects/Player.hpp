#pragma once
#include "RigidBody.hpp"
#include "weapons/Weapon.hpp"
class Player : public RigidBody {
public:
    Player(Vector2 pos);
    Player(Rectangle transform);
    void Update(float deltaTime) override;
    //void onCollision(const CollisionBody* other) override;
    void Draw() override;

    void MoveLeft();
    void MoveRight();
    void Fire();
    void Stop();
    Weapon* weapon;
private:
    Vector2 desiredMovement;
    int hp;
};