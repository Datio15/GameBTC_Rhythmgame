#include "Menu.h"
#include "SoundManager.h"
#include "InputHandler.h"
#include "Song.h"
using namespace std;
Menu::Menu(SDL_Renderer* rend) : renderer(rend), isActive(true) {
}

Menu::~Menu() {
    clean();
}
void Menu::init() {
	TextureManager::Instance()->load("Menu", "assets/image/Bemuse_menu.png", renderer);
	font = TTF_OpenFont("assets/font/Nunito.ttf", 30);
    if (!font) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else {
        std::cout << "Font loaded successfully!" << std::endl;
    }
	SoundManager::Instance()->loadMusic("menu", "assets/music/Menu_sound.mp3");
	SoundManager::Instance()->playMusic("menu", 1);
	isActive = true;
}
void Menu::handleEvents() {
    InputHandler::Instance()->update();

    if (InputHandler::Instance()->isKeyPressed(SDLK_LEFT)) {
        currentSongIndex = (currentSongIndex - 1 + songList.size()) % songList.size();
        selectedMusicPath = songList[currentSongIndex].songpath;
        selectedChartPath = songList[currentSongIndex].chartpath;
        selectedImagePath = songList[currentSongIndex].imagepath;
        SoundManager::Instance()->loadMusic("menu", selectedMusicPath);
        SoundManager::Instance()->playMusic("menu", 11);
    }

    if (InputHandler::Instance()->isKeyPressed(SDLK_RIGHT)) {
        currentSongIndex = (currentSongIndex + 1) % songList.size();
        selectedMusicPath = songList[currentSongIndex].songpath;
        selectedChartPath = songList[currentSongIndex].chartpath;
        selectedImagePath = songList[currentSongIndex].imagepath;
        SoundManager::Instance()->loadMusic("menu", selectedMusicPath);
        SoundManager::Instance()->playMusic("menu", 1);
    }

    if (InputHandler::Instance()->isKeyPressed(SDLK_RETURN)) {
        if (selectedMusicPath != "") {
            isActive = false;
            SoundManager::Instance()->stopMusic();
            TextureManager::Instance()->load("background", selectedImagePath, renderer);
        }
       
    }
}
void Menu::update() {
}
void Menu::render() {
	if (isActive) {
		SDL_RenderClear(renderer);
        TextureManager::Instance()->draw("Menu", 0, 0, 600, 780, renderer);
	}
    if (font) {
        SDL_Color textColor = { 255, 255, 255, 255 };
        const char* instruction = "Press Left Arrow to Choose Music";

        SDL_Surface* textSurface = TTF_RenderText_Blended(font, instruction, textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                SDL_Rect dstRect = {
                    75,            
                    480,            
                    textSurface->w,
                    textSurface->h
                };

                SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
                SDL_DestroyTexture(textTexture);
            }
            SDL_FreeSurface(textSurface);
        }
        
    }
    SDL_RenderPresent(renderer);

}
bool Menu::isMenuActive() const {
	return isActive;
}

void Menu::clean() {
	TextureManager::Instance()->clean();
}