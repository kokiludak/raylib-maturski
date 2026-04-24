#include "GameManager.hpp"

void GameManager::RegisterObject(GameObject* obj){
    objects.push_back(obj);
}

void GameManager::UnRegisterObject(GameObject* obj){
    //todo ne mogu sad o ovome da razmisljam
}

void GameManager::Update(float deltaTime){
    for(GameObject* obj : objects){
        obj->Update(deltaTime);
    }
}