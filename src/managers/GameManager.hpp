#pragma once
#include <vector>
#include "../objects/GameObject.hpp"
class GameManager {
public:
    void Update(float deltaTime);
    void RegisterObject(GameObject* obj);
    void UnRegisterObject(GameObject* obj);
private:
    std::vector<GameObject*> objects;
};