#pragma once
#include "Weapon.hpp"
#include "../CollisionBody.hpp"

class MachineGunBullet : public Bullet {
public:
    MachineGunBullet(float velocity);
    void Update(float deltaTime) override;
    void Draw() override;
private:
    float velocity;
};

class MachineGun : public Weapon {
public:
    MachineGun(int maxAmmo, float coolDown, float recoil) : Weapon(
        maxAmmo, coolDown, recoil
    )
    {}
    void OnFire(Vector2 position) override;
};