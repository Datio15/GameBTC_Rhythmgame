#include "InputHandler.h"

InputHandler* InputHandler::Instance() {
    static InputHandler instance;
    return &instance;
}

void InputHandler::update() {
    SDL_Event event;
    keyPressed.clear();
    keyReleased.clear();

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);  // Đóng game khi bấm nút X
            break;

        case SDL_KEYDOWN:
            if (!event.key.repeat) {
                keyPressed[event.key.keysym.sym] = true;
                keyHoldTime[event.key.keysym.sym] = SDL_GetTicks(); // Lưu thời gian bắt đầu giữ
            }
            break;

        case SDL_KEYUP:
            keyReleased[event.key.keysym.sym] = true;
            keyHoldTime.erase(event.key.keysym.sym); // Xóa thời gian giữ khi thả phím
            break;
        }
    }

    keystates = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    return keystates[key];
}

bool InputHandler::isKeyPressed(SDL_Keycode key) { // Nhấn 1 lần
    return keyPressed[key];
}

bool InputHandler::isKeyReleased(SDL_Keycode key) { // Thả phím
    return keyReleased[key];
}

bool InputHandler::isKeyHeld(SDL_Keycode key, Uint32 holdTime) { // Kiểm tra giữ phím lâu
    if (keyHoldTime.find(key) != keyHoldTime.end()) {
        return (SDL_GetTicks() - keyHoldTime[key]) >= holdTime;
    }
    return false;
}
