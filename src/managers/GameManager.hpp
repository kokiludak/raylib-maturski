#pragma once
#include <vector>
#include <memory>

class GameObject;

class GameManager {
public:
    void Update(float deltaTime);
    void Render();
    void RegisterObject(std::unique_ptr<GameObject> obj);
private:
    std::vector<std::unique_ptr<GameObject>> objects;
};