#include "GameManager.hpp"
#include "../objects/GameObject.hpp"
#include <iostream>
void GameManager::RegisterObject(std::unique_ptr<GameObject> obj){
    std::cout << "Added object\n";
    objects.push_back(std::move(obj));
}

void GameManager::Update(float deltaTime){
    for(auto& obj : objects){
        obj->Update(deltaTime);
        obj->Draw();
    }
}