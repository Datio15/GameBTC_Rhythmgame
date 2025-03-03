#ifndef NOTE_H
#define NOTE_H

#include <SDL.h>

class Note {
public:
    Note(int x, int y, int width,int height, int speed);
    void update();
    void render(SDL_Renderer* renderer);

    bool isOffScreen(); // Kiểm tra nếu nốt ra khỏi màn hình
	int getY(); // Lấy vị trí y của nốt
    int getLane();

private:
    int x, y;        // Vị trí nốt
	int width, height; // Kích thước nốt
    int speed;       // Tốc độ rơi
    SDL_Rect rect;   // Kích thước nốt
};

#endif
