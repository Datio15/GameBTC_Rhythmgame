#ifndef NOTE_H
#define NOTE_H

#include <SDL.h>

class Note {
public:
    Note(int x, int y, int width,int height, int speed);
    void update();
    void render(SDL_Renderer* renderer);

    bool isOffScreen(); 
	int getY(); 
    int getLane();

private:
    int x, y;   
	int width, height;
    int speed;       
    SDL_Rect rect;   
};

#endif
