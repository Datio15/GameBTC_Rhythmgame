#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureManager.h"

class Menu {
private:
    SDL_Renderer* renderer;
    bool isActive;
    TTF_Font* font;
    std::string selectedMusicPath = "";
	std::string selectedChartPath = "";
	std::string selectedImagePath = "";
    int currentSongIndex;
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void init();
    void handleEvents(); 
    void update();
    void render();
    bool isMenuActive() const;
    void clean();
    std::string getSelectedMusicPath() const { return selectedMusicPath; }
    std::string getSelectedChartPath() const { return selectedChartPath; }
    std::string getSelectedImagePath() const { return selectedImagePath; }
};

#endif