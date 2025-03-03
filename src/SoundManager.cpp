#include "SoundManager.h"

SoundManager* SoundManager::Instance() {
    static SoundManager instance;
    return &instance;
}

bool SoundManager::load(std::string id, std::string filePath) {
    Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
    if (chunk == nullptr) {
        return false;
    }
    sounds[id] = chunk;
    return true;
}

void SoundManager::play(std::string id) {
    Mix_PlayChannel(-1, sounds[id], 0);
}

void SoundManager::clean() {
    for (auto& sound : sounds) {
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();
}
