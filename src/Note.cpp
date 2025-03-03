#include "Note.h"

Note::Note(int x, int y,int width,int height, int speed) : x(x), y(y),speed(speed) {
	rect = { x, y, width, height };  // tọa độ và kích thước của nốt
}


void Note::update() {
    y += speed; // Nốt rơi xuống dần theo tốc độ
	rect.y = y;// ve vi tri moi cua rect
}

void Note::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
    SDL_RenderFillRect(renderer, &rect);
}
int Note::getY() {
	return y;
}
bool Note::isOffScreen() {
    return y > 600; // Nếu nốt rơi qua màn hình thì xóa
}
