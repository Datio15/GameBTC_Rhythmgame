#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <map>
#include <string>

class SoundManager {
public:
    static SoundManager* Instance();

    bool init();
    bool loadMusic(const std::string& id, const std::string& filePath);
    void playMusic(const std::string& id, int loop = -1);
    void stopMusic();
    void setMusicVolume(int volume);
    void clean();
    bool isMusicPlaying();

private:
    SoundManager();
    static SoundManager* s_pInstance;
    std::map<std::string, Mix_Music*> musics;
};
#endif