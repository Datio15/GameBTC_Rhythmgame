#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Note.h"
#include <sstream>
#include <fstream>
#include "AfterGame.h"
using namespace std;

Game::Game() :
    window(nullptr),
    renderer(nullptr),
    bgColorR(0),
    bgColorG(0),
    bgColorB(0),
    isRunning(false), comboDisplayTime(0),
    score(0){
    for (int i = 0; i < 4; i++) {
        laneEffectTime[i] = 0;
        laneEffectColor[i] = { 255, 255, 255, 50 };
    }
}

Game::~Game() {
    clean();
}

void Game::checkNoteHit(int lane) {
    bool noteFound = false;
    for (auto it = notes.begin(); it != notes.end();) {
        if (it->getLane() == lane) {
            int noteY = it->getY() + 20;
            if (noteY >= Judgment_Line - 20 && noteY <= Judgment_Line + 20) {
                currentJudgment = "Perfect";
                timeJudgment = 60;
                score += 100;
                combo++;
                perfecthit++;
                if (particleSystem) {
                    particleSystem->emitPerfectEffect(lane * 150 + 75, Judgment_Line);
                }
                laneEffectColor[lane] = getColorJudgment("Perfect");
                laneEffectColor[lane].a = 50;
                laneEffectTime[lane] = 18;
                noteFound = true;
                it = notes.erase(it);
                return;
            }
            else if ((noteY >= Judgment_Line - 40 && noteY <= Judgment_Line - 21) ||
                (noteY >= Judgment_Line + 21 && noteY <= Judgment_Line + 40)) {
                currentJudgment = "Good";
                timeJudgment = 60;
                score += 50;
                combo++;
                goodhit++;
                if (particleSystem) {
                    particleSystem->emitGoodEffect(lane * 150 + 75, Judgment_Line);
                }
                laneEffectColor[lane] = getColorJudgment("Good");
                laneEffectColor[lane].a = 50;
                laneEffectTime[lane] = 18;
                noteFound = true;
                it = notes.erase(it);
                return;
            }
            else if ((noteY >= Judgment_Line - 60 && noteY <= Judgment_Line - 41) ||
                (noteY >= Judgment_Line + 41 && noteY <= Judgment_Line + 60)) {
                currentJudgment = "Bad";
                timeJudgment = 60;
                score += 20;
                combo++;
                badhit++;
                if (particleSystem) {
                    particleSystem->emitBadEffect(lane * 150 + 75, Judgment_Line);
                }
                laneEffectColor[lane] = getColorJudgment("Bad");
                laneEffectColor[lane].a = 50;
                laneEffectTime[lane] = 18;
                noteFound = true;
                it = notes.erase(it);
                return;
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }

        if (combo > maxCombo) {
            maxCombo = combo;
        }
    }

    InputHandler* input = InputHandler::Instance();
    SDL_Keycode keys[4] = { SDLK_a, SDLK_s, SDLK_d, SDLK_f };

    if (input->isKeyPressed(keys[lane]) && !noteFound) {
        laneEffectTime[lane] = 18;
        laneEffectColor[lane] = { 255, 255, 255, 50 };
    }
}



void Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "SDL initialized!" << endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window) {
            cout << "Window created!" << endl;
        }
        else {
            cout << "Window creation failed: " << SDL_GetError() << endl;
            isRunning = false;
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, bgColorR, bgColorG, bgColorB, 255);
            cout << "Renderer created!" << endl;
        }
        else {
            cout << "Renderer creation failed: " << SDL_GetError() << endl;
            isRunning = false;
            return;
        }
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
            isRunning = false;
            return;
        }

        // Khởi tạo âm thanh
        if (SoundManager::Instance()->init()) {
            cout << "Sound system initialized!" << endl;
        }
        else {
            cout << "Sound system initialization failed!" << endl;
        }
        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        }
		fontScore = TTF_OpenFont("assets/font/Nunito.ttf", 26);
		fontJudgment = TTF_OpenFont("assets/font/Allerta.ttf", 40);
		fontCombo = TTF_OpenFont("assets/font/Allerta.ttf", 35);

		menu = new Menu(renderer);
		menu->init();
		afterGame = new AfterGame(renderer);
        particleSystem = new ParticleSystem(renderer, this);
        // Khởi tạo random seed
        if (menu->isMenuActive()) {
            SoundManager::Instance()->playMusic("music", -1);
        }
		
        srand(static_cast<unsigned int>(time(nullptr)));

        score = 0;
        isRunning = true;
		SoundManager::Instance()->setMusicVolume(58);
    }
    else {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        isRunning = false;
    }
}

void Game::handleEvents() {
    if (menu->isMenuActive()) {
        menu->handleEvents();
       
    }
    else if (afterGame && afterGame->isActive()) {
        afterGame->handleEvents();
    }
    else {
        InputHandler* input = InputHandler::Instance();
        input->update();
        const SDL_Keycode keys[] = { SDLK_a, SDLK_s, SDLK_d, SDLK_f };
        if (input->isKeyPressed(keys[0])) {
            checkNoteHit(0);
        }
        if (input->isKeyPressed(keys[1])) {
            checkNoteHit(1);
        }
        if (input->isKeyPressed(keys[2])) {
            checkNoteHit(2);
        }
        if (input->isKeyPressed(keys[3])) {
            checkNoteHit(3);
        }
		if (input->isKeyPressed(SDLK_ESCAPE)) {
			SoundManager::Instance()->stopMusic();
            afterGame->results(goodhit, perfecthit, badhit, misshit, maxCombo, score);
            afterGame->init();
		}
    }
}


void Game::update() {
    if (menu->isMenuActive()) return menu->update();
    else if (afterGame->isActive()) {
        if (afterGame->shouldGoToMenu()) {
            menu->init(); afterGame->clean(); delete afterGame;
            afterGame = new AfterGame(renderer);
            score = combo = maxCombo = goodhit = perfecthit = badhit = misshit = 0;
            notes.clear(); noteChart.clear(); nextNoteIndex = 0;
            currentJudgment = ""; timeJudgment = 0;
            SoundManager::Instance()->playMusic("menu", -1);
            return;
        }
    }
    else {
        if (noteChart.empty()) {
            loadChartFromFile(menu->getSelectedChartPath());
			SoundManager::Instance()->loadMusic("music", menu->getSelectedMusicPath());
            SoundManager::Instance()->playMusic("music", 1);
            startTimeMs = SDL_GetTicks();
        }
		if (SoundManager::Instance()->isMusicPlaying() == false) {
            afterGame->results(goodhit, perfecthit, badhit, misshit, maxCombo, score);
            afterGame->init();
		}

        Uint32 currentTime = SDL_GetTicks() - startTimeMs;
        while (nextNoteIndex < noteChart.size() && currentTime >= noteChart[nextNoteIndex].timeMs) {
            int lane = noteChart[nextNoteIndex].lane;
            notes.emplace_back(Note(lane * 150, 0, 150, 20, 6));
            nextNoteIndex++;
        }

        for (auto& note : notes) note.update();
        auto it = notes.begin();
        while (it != notes.end()) {
            if (it->isOffScreen()) {
                currentJudgment = "Miss"; timeJudgment = 60;
                combo = 0; misshit++;
                if (particleSystem) particleSystem->emitMissEffect(it->getLane() * 150 + 75, Judgment_Line);
                it = notes.erase(it);
            }
            else ++it;
        }

        if (timeJudgment > 0 && --timeJudgment == 0) currentJudgment = "";
        static int prevCombo = 0;
        if (combo != prevCombo && combo > 3) {
            comboDisplayTime = 30;
            prevCombo = combo;
        }
        if (comboDisplayTime > 0) comboDisplayTime--;
        for (int i = 0; i < 4; ++i) if (laneEffectTime[i] > 0) laneEffectTime[i]--;
    }
}


void Game::render() {
    if (menu->isMenuActive()) {
        menu->render();
    }
    else if (afterGame && afterGame->isActive()) {
        afterGame->render();
        return;
    }
    else {
        SDL_SetRenderDrawColor(renderer, bgColorR, bgColorG, bgColorB, 255);
        SDL_RenderClear(renderer);

        TextureManager::Instance()->draw("background", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
        for (int i = 0; i < 4; i++) {
            if (laneEffectTime[i] > 0) {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, laneEffectColor[i].r, laneEffectColor[i].g, laneEffectColor[i].b, laneEffectColor[i].a);
                SDL_Rect laneRect = { i * 150, 0, 150, SCREEN_HEIGHT };
                SDL_RenderFillRect(renderer, &laneRect);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 1; i < 4; i++) {
           SDL_RenderDrawLine(renderer, i * 150, 0, i * 150, SCREEN_HEIGHT);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, 0, Judgment_Line, SCREEN_WIDTH, Judgment_Line);
		SDL_RenderDrawLine(renderer, 0, Judgment_Line - 20, SCREEN_WIDTH, Judgment_Line - 20);

        for (auto& note : notes) {
            note.render(renderer);
        }
		if (particleSystem) {
			particleSystem->render();
			particleSystem->update();
		}
        if(fontScore) {
            std::stringstream ss;
            ss << "Score: " << score;
            SDL_Color textColor = { 255, 255, 255, 255 };
            SDL_Surface* textSurface = TTF_RenderText_Solid(fontScore, ss.str().c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_Rect dstRect = { 10, 10, textSurface->w, textSurface->h };
                    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
        if (currentJudgment != "" && fontJudgment) {
            SDL_Color textColor = getColorJudgment(currentJudgment);
            SDL_Color glowColor = textColor;
            glowColor.a = 100;
            SDL_Surface* glowSurface = TTF_RenderText_Solid(fontJudgment, currentJudgment.c_str(), glowColor);
            if (glowSurface) {
                SDL_SetTextureBlendMode(SDL_CreateTextureFromSurface(renderer, glowSurface), SDL_BLENDMODE_BLEND);
                SDL_Texture* glowTexture = SDL_CreateTextureFromSurface(renderer, glowSurface);
                if (glowTexture) {
                    SDL_Rect glowRect = { SCREEN_WIDTH / 2 - glowSurface->w / 2 - 2, Judgment_Line - 80 - 2, glowSurface->w + 4, glowSurface->h + 4 };
                    SDL_RenderCopy(renderer, glowTexture, nullptr, &glowRect);
                    glowRect.x += 2;
                    SDL_RenderCopy(renderer, glowTexture, nullptr, &glowRect);
                    glowRect.x -= 4;
                    SDL_RenderCopy(renderer, glowTexture, nullptr, &glowRect);
                    glowRect.x += 2;
                    glowRect.y += 2;
                    SDL_RenderCopy(renderer, glowTexture, nullptr, &glowRect);
                    glowRect.y -= 4;
                    SDL_RenderCopy(renderer, glowTexture, nullptr, &glowRect);
                    SDL_DestroyTexture(glowTexture);
                }
                SDL_FreeSurface(glowSurface);
            }
        }

        if (combo > 3 && fontCombo && comboDisplayTime > 0) {
            std::stringstream ss;
            ss << "Combo x" << combo;
            SDL_Color textColor = getColorCombo(combo);
            SDL_Surface* textSurface = TTF_RenderText_Solid(fontCombo, ss.str().c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    float scale = 1.0f + 0.5f * (comboDisplayTime / 30.0f);
                    SDL_Rect dstRect = {
                        10 - static_cast<int>((textSurface->w * scale - textSurface->w) / 2),
                        50 - static_cast<int>((textSurface->h * scale - textSurface->h) / 2),
                        static_cast<int>(textSurface->w * scale),
                        static_cast<int>(textSurface->h * scale)
                    };
                    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }

        SDL_RenderPresent(renderer);
    }
}

void Game::clean() {
    if (menu) {
        delete menu;
        menu = nullptr;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (particleSystem) {
        delete particleSystem;
        particleSystem = nullptr;
    }

    TextureManager::Instance()->clean();
    SoundManager::Instance()->clean();

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
SDL_Color Game::getColorJudgment(const std::string& judgment) {
	if (judgment == "Perfect") {
		return { 0, 255, 0, 255 };
	}
	else if (judgment == "Good") {
		return { 255, 255, 0, 255 };
	}
	else if (judgment == "Bad") {
		return { 255, 165, 0, 255 };
	}
	else if (judgment == "Miss") {
		return { 255, 0, 0, 255 };
	}
	return { 255, 255, 255, 255 };
}
SDL_Color Game:: getColorCombo (const int combo) {
    if (combo < 10) return { 180, 180, 180, 255 };
    else if (combo < 30) return { 0, 200, 255, 255 };
    else if (combo < 60) return { 180, 100, 255, 255 };
    else if (combo < 100) return { 255, 64, 128, 255 };
    else return { 255, 255, 100, 255 };
}

void Game::loadChartFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Không thể mở chart: " << path << std::endl;
        return;
    }

    int time, lane;
    while (file >> time >> lane) {
        noteChart.push_back({ time, lane });
    }
}