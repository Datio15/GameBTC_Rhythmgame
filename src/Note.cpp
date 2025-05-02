#include "Note.h"

Note::Note(int x, int y, int width, int height, int speed) :
    x(x),
    y(y),
    width(width),  
    height(height),  
    speed(speed) {
    rect = { x, y, width, height };
}

void Note::update() {
    y += speed;
    rect.y = y;
}

void Note::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int Note::getY() {
	return y;
}

int Note::getLane() {
    if (x < 150) return 0;
    else if (x >= 150 && x < 300) return 1;
    else if (x >= 300 && x < 450) return 2;
    else return 3;
}

bool Note::isOffScreen() {
    return y > 780;
}
