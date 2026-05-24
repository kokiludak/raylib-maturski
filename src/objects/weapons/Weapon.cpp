#include "Weapon.hpp"

void Weapon::Update(float deltaTime){
    currentCooldown -= deltaTime;
}

void Weapon::CoolDown(){
    currentCooldown = cooldownTime;
}

void Weapon::Reload(){
    currentAmmo = maxAmmo;
}

float Weapon::GetRecoil(){
    return recoil;
}

int Weapon::GetCurrentAmmo(){
    return currentAmmo;
}

bool Weapon::Fire(Vector2 position){
    if(currentCooldown > 0.0f) return false;

    if(currentAmmo <= 0) return false;

    OnFire(position);
    currentAmmo--;
    CoolDown();
    return true;
}