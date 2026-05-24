#pragma once
#include <string>
#include <raylib.h>
#include <unordered_map>

class TextureCache {
public:
    static Texture2D& Get(const std::string& path);
    static void UnloadAll();
private:
    static std::unordered_map<std::string, Texture2D>& GetCache() {
        static std::unordered_map<std::string, Texture2D> cache;
        return cache;
    }
};  