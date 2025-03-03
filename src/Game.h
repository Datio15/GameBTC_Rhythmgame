#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "TextureManager.h"
#include "InputHandler.h"
#include "SoundManager.h"

class Game {
public:
    Game();
	~Game();
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
	Uint8 bgColorR = 0, bgColorB = 0, bgColorG = 0;
    bool isRunning;
};

#endif
