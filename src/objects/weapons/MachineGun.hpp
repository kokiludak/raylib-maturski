#pragma once
#include "Weapon.hpp"
#include "../CollisionBody.hpp"

class MachineGunBullet : public Bullet {
public:
    MachineGunBullet(float velocity);
    void Update(float deltaTime);
private:
    float velocity;
};

class MachineGun : public Weapon {
public:
    bool Fire(Vector2 position) override;
    float GetRecoil() override;
    MachineGun(int ammo, float recoil, float CoolDownTime);
};