#pragma once
#include <string>
#include <raylib.h>
#include "../managers/TextureCache.hpp"

class TexturedObject {
public:
    TexturedObject(const std::string& path){
        texture = &TextureCache::Get(path);
    }
    void DrawStretched(Rectangle dest){
        Rectangle source = {0, 0, (float)texture->width, (float)texture->height };
        DrawTexturePro(*texture, source, dest, {0, 0}, 0.0f, WHITE);
    }
protected:
    Texture2D* texture = nullptr;
};