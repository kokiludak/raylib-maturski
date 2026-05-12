#pragma once
#include <functional>
#include <memory>


class GameObject;
using SpawnCallback = std::function<void(std::unique_ptr<GameObject>)>;

class SpawnBus {
public:
    static void Register(SpawnCallback cb) {callback = cb;}

    template<typename T, typename... Args>
    static T* Spawn(Args&&... args) {
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = obj.get();
        if(callback)
            callback(std::move(obj));
        return raw;
    }
private:
    // automatski bude nullptr
   static SpawnCallback callback;
};