#include "AfterGame.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SDL_ttf.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Menu.h"
AfterGame::AfterGame(SDL_Renderer* rend) : renderer(rend), active(false), returnMenu(false) {
	fontLarge = nullptr;
	fontSmall = nullptr;
	resultText = "";
	goodNotes = 0;
	perfectNotes = 0;
	badNotes = 0;
	missNotes = 0;
	finalScore = 0;
	finalMaxCombo = 0;
	percentHit = 0.0f;
	rank = 'F';
}
AfterGame::~AfterGame() {
	clean();
}
void AfterGame::init() {
	TextureManager::Instance()->load("aftergame", "assets/image/result.jpg", renderer);
	fontLarge = TTF_OpenFont("assets/font/Nunito.ttf", 40);
	fontSmall = TTF_OpenFont("assets/font/Nunito.ttf", 30);
	if (!fontLarge || !fontSmall) {
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	backButtonRect = { 180, 550, 240, 50 };
	active = true;
}
void AfterGame::results(int good, int perfect, int bad, int missed, int maxCombo, int score) {
	badNotes = bad;
	goodNotes = good;
	perfectNotes = perfect;
	missNotes = missed;
	finalScore = score;
	finalMaxCombo = maxCombo;

	int totalHit = bad + good + perfect;
	int total = totalHit + missed;
	percentHit = (total == 0) ? 0.0f : (float)totalHit / total * 100.0f;

	if (percentHit == 100.0f && missed == 0) rank = 'S';
	else if (percentHit >= 95.0f) rank = 'A';
	else if (percentHit >= 90.0f) rank = 'B';
	else if (percentHit >= 80.0f) rank = 'C';
	else rank = 'D';
}
void AfterGame::handleEvents() {
	InputHandler::Instance()->update();
	if (InputHandler::Instance()->isKeyPressed(SDLK_SPACE)) {
		returnMenu = true;
	}
}
void AfterGame::render() {
	if (active) {
		SDL_RenderClear(renderer);
		TextureManager::Instance()->draw("aftergame", 0, 0, 600, 780, renderer);
		SDL_Color white = { 255, 255, 255, 255 };
		SDL_Color purple = { 200,150,255,255 };
		SDL_Color rankColor = getColorRank(rank);
		if (fontLarge) {
			SDL_Color white = { 255, 255, 255, 255 };
			SDL_Surface* titleSurf = TTF_RenderText_Solid(fontLarge, "Results", white);
			SDL_Texture* titleTex = SDL_CreateTextureFromSurface(renderer, titleSurf);

			SDL_Rect titleRect = {
				300 - titleSurf->w / 2, 30,
				titleSurf->w,
				titleSurf->h
			};

			SDL_RenderCopy(renderer, titleTex, nullptr, &titleRect);

			SDL_FreeSurface(titleSurf);
			SDL_DestroyTexture(titleTex);
		}
		int y = 100;
		std::vector<LabelData> lines = {
		{"Bad Notes Hit: ", std::to_string(badNotes), {0, 200, 255, 255}},
		{"Good Notes Hit: ", std::to_string(goodNotes), {255, 165, 0, 255}},
		{"Perfect Notes Hit: ", std::to_string(perfectNotes), {0, 255, 0, 255}},
		{"Missed Notes: ", std::to_string(missNotes), {255, 0, 0, 255}},
		{"Max Combo: ", std::to_string(finalMaxCombo), {255, 255, 0, 255}},
		{"Percentage Hit: ", std::to_string((int)percentHit) + "%", {200, 150, 255, 255}}
		};
		for (const auto& line : lines) {
			SDL_Surface* labelSurface = TTF_RenderText_Solid(fontSmall, line.label.c_str(), white);
			SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
			SDL_Rect labelRect = { 100, y, labelSurface->w, labelSurface->h };
			SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);

			SDL_Surface* valueSurface = TTF_RenderText_Solid(fontSmall, line.value.c_str(), line.valueColor);
			SDL_Texture* valueTexture = SDL_CreateTextureFromSurface(renderer, valueSurface);
			SDL_Rect valueRect = { 400, y, valueSurface->w, valueSurface->h };
			SDL_RenderCopy(renderer, valueTexture, nullptr, &valueRect);

			SDL_FreeSurface(labelSurface);
			SDL_DestroyTexture(labelTexture);
			SDL_FreeSurface(valueSurface);
			SDL_DestroyTexture(valueTexture);

			y += 40;
		}
		std::string r(1, rank);
		SDL_Surface* rankSurf = TTF_RenderText_Solid(fontLarge, r.c_str(), rankColor);
		SDL_Texture* rankTex = SDL_CreateTextureFromSurface(renderer, rankSurf);
		SDL_Rect rankDst = { 290, y + 10, rankSurf->w, rankSurf->h };
		SDL_RenderCopy(renderer, rankTex, nullptr, &rankDst);
		SDL_FreeSurface(rankSurf);
		SDL_DestroyTexture(rankTex);


		SDL_Surface* finalLabel = TTF_RenderText_Solid(fontSmall, "Final Score", white);
		SDL_Texture* finalLabelTex = SDL_CreateTextureFromSurface(renderer, finalLabel);
		SDL_Rect finalLabelRect = { 250, y + 70, finalLabel->w, finalLabel->h };
		SDL_RenderCopy(renderer, finalLabelTex, nullptr, &finalLabelRect);
		SDL_FreeSurface(finalLabel);
		SDL_DestroyTexture(finalLabelTex);


		SDL_Surface* scoreSurface = TTF_RenderText_Blended(fontLarge, std::to_string(finalScore).c_str(), purple);
		SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
		SDL_Rect scoreDst = { 200, y + 120, scoreSurface->w, scoreSurface->h };
		SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreDst);
		SDL_FreeSurface(scoreSurface);
		SDL_DestroyTexture(scoreTexture);


		SDL_SetRenderDrawColor(renderer, 60, 180, 220, 255);
		SDL_RenderFillRect(renderer, &backButtonRect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &backButtonRect);

		SDL_Surface* btnText = TTF_RenderText_Solid(fontSmall, "MAIN MENU", white);
		SDL_Texture* btnTex = SDL_CreateTextureFromSurface(renderer, btnText);
		SDL_Rect btnTextRect = {
			backButtonRect.x + (backButtonRect.w - btnText->w) / 2,
			backButtonRect.y + (backButtonRect.h - btnText->h) / 2,
			btnText->w,
			btnText->h
		};
		SDL_RenderCopy(renderer, btnTex, nullptr, &btnTextRect);
		SDL_FreeSurface(btnText);
		SDL_DestroyTexture(btnTex);

		SDL_RenderPresent(renderer);
	}
}
bool AfterGame::isActive() const {
	return active;
}

SDL_Color AfterGame::getColorRank(char r) {
	switch (r) {
	case 'S': return { 0, 255, 255, 255 };
	case 'A': return { 0, 255, 0, 255 };
	case 'B': return { 100, 200, 255, 255 };
	case 'C': return { 255, 255, 0, 255 };
	case 'D': return { 255, 100, 100, 255 };
	default:  return { 255, 255, 255, 255 };
	}
}
void AfterGame::clean() {
	if (fontLarge != nullptr) {
		TTF_CloseFont(fontLarge);
		fontLarge = nullptr;
	}
	if (fontSmall != nullptr) {
		TTF_CloseFont(fontSmall);
		fontSmall = nullptr;
	}
}
