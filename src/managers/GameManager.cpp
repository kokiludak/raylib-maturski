#include "GameManager.hpp"
#include "../objects/GameObject.hpp"
#include <iostream>
void GameManager::RegisterObject(std::unique_ptr<GameObject> obj){
    objects.push_back(std::move(obj));
}

void GameManager::Update(float deltaTime){
    for(auto& obj : objects){
        obj->Update(deltaTime);
    }
}

void GameManager::Render(){
    for(auto& obj : objects){
        obj->Draw();
    }
}