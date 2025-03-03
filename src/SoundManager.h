#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <map>
#include <string>

class SoundManager {
public:
    static SoundManager* Instance();
    bool load(std::string id, std::string filePath);
    void play(std::string id);
    void clean();

private:
    SoundManager() {}
    std::map<std::string, Mix_Chunk*> sounds;
};

#endif
