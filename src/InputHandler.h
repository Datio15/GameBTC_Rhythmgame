#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include <iostream>
#include <map>// luu trang thai cua phim

class InputHandler {// ớp InputHandler chịu trách nhiệm quản lý đầu vào bàn phím trong SDL.
public:
    static InputHandler* Instance(); //Đảm bảo chỉ có một thể hiện duy nhất(Instance-mo hinh don le) của InputHandler tồn tại trong chương trình.

	void update();// Cập nhật trạng thái của các phím trong moi vong lap game
	bool isKeyDown(SDL_Scancode key);// Kiểm tra xem một phím nào đó có được nhấn xuống không Sử dụng SDL_Scancode (mã quét của phím).
	bool isKeyPressed(SDL_Keycode key);// Kiểm tra xem một phím nào đó có được nhấn xuống và thả ra ngay lập tức không SDL_Keycode (mã của phím theo ký tự ASCII).
	bool isKeyReleased(SDL_Keycode key); // Kiểm tra xem một phím nào đó có được thả ra không
    bool isKeyHeld(SDL_Keycode key, Uint32 holdTime); // Kiểm tra giữ phím lâu

private:
    InputHandler() {} // Constructor private

    std::map<SDL_Keycode, bool> keyPressed;
    std::map<SDL_Keycode, bool> keyReleased;
    std::map<SDL_Keycode, Uint32> keyHoldTime; // Lưu thời gian giữ phím

    const Uint8* keystates = nullptr;
};

#endif
