#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include <iostream>
#include <map>

class InputHandler {
public:
    static InputHandler* Instance();

    void update();
    bool isKeyPressed(SDL_Keycode key);
private:
    InputHandler() {}

    std::map<SDL_Keycode, bool> keyPressed;

    const Uint8* keystates = nullptr;
    int volume = 68;
};

#endif
