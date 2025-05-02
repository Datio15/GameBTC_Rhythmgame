#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "Note.h"
#include <iostream>
#include <ctime>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char* argv[]) {

    Uint32 frameStart;
    int frameTime;

    Game* game = new Game();
    game->init("Bemuse", 600, 780);
    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();        
        game->render();        

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    game->clean();
    delete game;
    game = nullptr;
    return 0;
}
