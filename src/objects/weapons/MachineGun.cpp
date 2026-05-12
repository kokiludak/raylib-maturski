#include "MachineGun.hpp"

#include <raylib.h>

void MachineGunBullet::Update(float deltaTime){
    Translate({0, velocity * deltaTime});
}

MachineGunBullet::MachineGunBullet(float velocity) : velocity(velocity){
    //molim te promeni ovo
    SetTransform({0, 0, 50, 50});
}

void MachineGunBullet::Draw(){
    Vector2 position = GetCenter();
    DrawCircle(position.x, position.y, GetTransform().width, RAYWHITE);
}

void MachineGun::OnFire(Vector2 position){
    MachineGunBullet* bullet = SpawnBus::Spawn<MachineGunBullet>(3000);
    bullet->SetCenter(position);
}
