#pragma once
#include "RigidBody.hpp"
#include "weapons/Weapon.hpp"
class Player : public RigidBody {
public:
    ~Player(){
        delete weapon;
    }
    Player(Vector2 pos);
    Player(Rectangle transform);
    void Update(float deltaTime) override;
    void OnCollision(const CollisionBody* other) override;
    void Draw() override;
    
    int GetHealth(){
        return hp;
    }
    void MoveLeft();
    void MoveRight();
    void Fire();
    void Stop();
    Weapon* weapon = nullptr;
private:
    Vector2 desiredMovement;
    int hp = 4;
    float invulnerabilityTime = 1.0f;
    float currentInvulnerability = invulnerabilityTime;
};