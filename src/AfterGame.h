#ifndef AFTERGAME_H
#define AFTERGAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Menu.h"

class AfterGame {
public:
	AfterGame(SDL_Renderer* renderer);
	~AfterGame();

	void init();
	void handleEvents();
	void render();
	bool isActive() const;
	void clean();
	void results(int good, int perfect, int bad,int miss, int maxCombo,int score);
	bool shouldGoToMenu() const { return returnMenu; }
	SDL_Color getColorRank(char rank);
private:
	SDL_Renderer* renderer;
	bool active;
	bool returnMenu;
	TTF_Font* fontLarge;
	TTF_Font* fontSmall;
	std::string resultText;
	int goodNotes;
	int perfectNotes;
	int badNotes;
	int missNotes;
	int finalScore;
	int finalMaxCombo;
	float percentHit;
	char rank;
	SDL_Rect backButtonRect;
	Menu* menu;
};
struct LabelData{
		std::string label;
		std::string value;
		SDL_Color valueColor;
};
#endif
