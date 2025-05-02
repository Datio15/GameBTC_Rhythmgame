#include "InputHandler.h"
#include "SoundManager.h"

InputHandler* InputHandler::Instance() {
    static InputHandler instance;
    return &instance;
}

void InputHandler::update() {
    SDL_Event event;
    keyPressed.clear();

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            if (!event.key.repeat) {
                keyPressed[event.key.keysym.sym] = true;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                if (volume < 128) {
                    volume += 8;
					SoundManager::Instance()->setMusicVolume(volume);
            }
        }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                if (volume > 0) {
                    volume -= 8;
					SoundManager::Instance()->setMusicVolume(volume);
    }
}
            break;

bool InputHandler::isKeyDown(SDL_Scancode key) {
    return keystates[key];
}

bool InputHandler::isKeyPressed(SDL_Keycode key) { // Nhấn 1 lần
    return keyPressed[key];
}
}

    keystates = SDL_GetKeyboardState(nullptr);
    }
bool InputHandler::isKeyPressed(SDL_Keycode key) { 
    return keyPressed[key];
}
