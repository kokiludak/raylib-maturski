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
    Weapon(
        int maxAmmo,
        float cooldownTime,
        float recoil
    ) :
    cooldownTime(cooldownTime),
    currentCooldown(0.0f),
    recoil(recoil),
    maxAmmo(maxAmmo),
    currentAmmo(maxAmmo)
    {}

    virtual ~Weapon() = default;

    void Update(float deltaTime);

    //mozda nije pametno
    void CoolDown();
    void Reload();
    bool Fire(Vector2 position);
    float GetRecoil();
protected:
    float cooldownTime;
    float currentCooldown;
    float recoil;

    virtual void OnFire(Vector2 position) {};
private:
    int maxAmmo;
    int currentAmmo;
};