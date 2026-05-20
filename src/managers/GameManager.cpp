#include "GameManager.hpp"
#include "../objects/GameObject.hpp"
#include <algorithm>
#include <iostream>
void GameManager::RegisterObject(std::unique_ptr<GameObject> obj){
    RigidBody* rb = dynamic_cast<RigidBody*>(obj.get());
    CollisionBody* cb = dynamic_cast<CollisionBody*>(obj.get());

    objects.push_back(std::move(obj));

    //mozda moze da se resi sa jos observera...
    if(rb) physics.RegisterBody(rb);
    else if(cb) {
        physics.RegisterCollider(cb);
    }
}

void GameManager::Update(float deltaTime){
    //std::cout << "alive objects: " << objects.size() << '\n';

    for(auto& obj : objects){
        if(obj->alive)
            obj->Update(deltaTime);
    }

    for(auto& obj : objects){
        if(!obj->alive){
            CollisionBody* cb = dynamic_cast<CollisionBody*>(obj.get());
            RigidBody* rb = dynamic_cast<RigidBody*>(obj.get());
            if(rb){
                physics.UnRegisterBody(rb);
            }
            else if(cb){
                physics.UnRegisterCollider(cb);
            }
        }
    }
    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                [](const std::unique_ptr<GameObject>& obj){
                    return !obj->alive;
                }),
            objects.end()
    );
}


//TODO: z index
void GameManager::Render(){
    for(auto& obj : objects){
        if(obj->alive){
            obj->Draw();
        }
    }
}