#pragma once
#include <vector>
#include <memory>
#include "Physics.hpp"
class GameObject;

class GameManager {
public:
    GameManager(Physics& physics) : physics(physics) {}
    void Update(float deltaTime);
    void Render();
    void RegisterObject(std::unique_ptr<GameObject> obj);
    
private:
    Physics& physics;
    std::vector<std::unique_ptr<GameObject>> objects;
};