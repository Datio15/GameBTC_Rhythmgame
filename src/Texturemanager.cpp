#include "TextureManager.h"

TextureManager* TextureManager::Instance() {
    static TextureManager instance;
    return &instance;
}

bool TextureManager::load(std::string id, std::string filePath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        std::cout << "Lỗi load ảnh: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        std::cout << "Lỗi tạo texture: " << SDL_GetError() << std::endl;
        return false;
    }

    textures[id] = texture;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer) {
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, textures[id], &srcRect, &destRect);
}

void TextureManager::clean() {
    for (auto& t : textures) {
        SDL_DestroyTexture(t.second);
    }
    textures.clear();
}
