#pragma once
#include <vector>
#include <memory>
#include "Physics.hpp"
class GameObject;

class GameManager {
public:
    void Update(float deltaTime);
    void Render();
    void RegisterObject(std::unique_ptr<GameObject> obj);
    Physics* physics;
private:
    std::vector<std::unique_ptr<GameObject>> objects;
};