#include "MachineGun.hpp"
#include <raylib.h>

void MachineGunBullet::Update(float deltaTime){
    Translate({0, velocity * deltaTime});
}

MachineGunBullet::MachineGunBullet(float velocity) : velocity(velocity){
    //molim te promeni ovo
    SetTransform({GetTransform().x, GetTransform().y, 50, 50});
}

void MachineGunBullet::Draw(){
    Vector2 position = GetCenter();
    DrawCircle(position.x, position.y, GetTransform().width, RAYWHITE);
}

MachineGun::MachineGun(int ammo, float recoil, float cooldownTime){
    this->ammo = ammo;
    this->recoil = recoil;
    this->cooldownTime = cooldownTime;
}

float MachineGun::GetRecoil(){
    return recoil;
}

bool MachineGun::Fire(Vector2 position){
    if(currentCooldown > 0) return false;
    //ovo je verovatno uzasno
    MachineGunBullet* bullet = GameObject::Instantiate<MachineGunBullet>(3000);
    bullet->SetCenter(position);
    currentCooldown = cooldownTime;
    return true;
}
