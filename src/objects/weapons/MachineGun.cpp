#include "MachineGun.hpp"


void MachineGunBullet::Update(float deltaTime){
    Translate({0, velocity * deltaTime});
}

MachineGunBullet::MachineGunBullet(float velocity) : velocity(velocity){}

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
    MachineGunBullet bullet(100);
    bullet.SetPosition(position);
    currentCooldown = cooldownTime;
    return true;
}
