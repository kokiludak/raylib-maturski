#pragma once
#include <vector>
#include <raylib.h>
#include "../CollisionBody.hpp"
class Bullet : public CollisionBody {
public:
    int damage;
};

class Weapon {
public:
    void Update(float deltaTime);
    virtual bool Fire(Vector2 position) = 0;
    virtual float GetRecoil() = 0;
protected:
    int ammo;
    float cooldownTime;
    float currentCooldown;
    float recoil;
};