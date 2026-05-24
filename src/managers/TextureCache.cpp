#include "TextureCache.hpp"
#include <raylib.h>
#include <iostream>
Texture2D& TextureCache::Get(const std::string& path){
    auto& cache = GetCache();
    if(cache.find(path) == cache.end())
        cache[path] = LoadTexture(path.c_str());
    return cache[path];
}

void TextureCache::UnloadAll(){
    auto& cache = GetCache();
    for(auto& [path, tex] : cache){
        UnloadTexture(tex);
    }
    cache.clear();
}
