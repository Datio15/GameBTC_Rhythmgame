#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager::TextureManager() {
}

TextureManager* TextureManager::Instance() {
    if (s_pInstance == nullptr) {
        s_pInstance = new TextureManager();
}
    return s_pInstance;
}

bool TextureManager::load(std::string id, std::string filePath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        std::cout << "Error loading image: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
        return false;
    }

    textures[id] = texture;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer) {
    auto it = textures.find(id);
    if (it != textures.end()) {
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x, y, width, height };
        SDL_RenderCopy(renderer, it->second, &srcRect, &destRect);
    }
    else {
        std::cout << "Texture with ID " << id << " not found!" << std::endl;
    }
}

void TextureManager::clean() {
    for (auto& t : textures) {
        SDL_DestroyTexture(t.second);
    }
    textures.clear();

    delete s_pInstance;
    s_pInstance = nullptr;
}
