#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <string>

class TextureManager {
public:
    static TextureManager* Instance();

    bool load(std::string id, std::string filePath, SDL_Renderer* renderer);
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer);
    void clean();

private:
    TextureManager();
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> textures;
};

#endif
