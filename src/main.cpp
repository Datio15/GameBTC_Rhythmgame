#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "Note.h"
Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();
    game->init("Anime Girl",600,600);

    while (game->running()) {
        game->handleEvents();
        game->update();        
        game->render();        
        SDL_Delay(16);         
    }

    game->clean();
    return 0;
}
