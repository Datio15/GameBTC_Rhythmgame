#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::s_pInstance = nullptr;

SoundManager::SoundManager() {
}

SoundManager* SoundManager::Instance() {
    if (s_pInstance == nullptr) {
        s_pInstance = new SoundManager();
    }
    return s_pInstance;
}

bool SoundManager::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SoundManager::loadMusic(const std::string& id, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    musics[id] = music;
    return true;
}



void SoundManager::playMusic(const std::string& id, int loop) {
    if (musics.find(id) != musics.end()) {
        Mix_PlayMusic(musics[id], loop);
    }
}


void SoundManager::stopMusic() {
    Mix_HaltMusic();
}
bool SoundManager::isMusicPlaying() {
    return Mix_PlayingMusic();
}

void SoundManager::setMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}

void SoundManager::clean() {
    for (auto& music : musics) {
        Mix_FreeMusic(music.second);
    }
    musics.clear();

    Mix_CloseAudio();

    delete s_pInstance;
    s_pInstance = nullptr;
}
