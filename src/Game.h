#ifndef GAME_H
#define GAME_H
#include "ParticleSystem.h"
#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "Note.h"
#include "Menu.h"
#include "AfterGame.h"
struct NoteEvent {
    int timeMs;
    int lane;
};
const int PERFECT_WINDOW = 30;
const int GOOD_WINDOW = 80;
const int BAD_WINDOW = 150;
class ParticleSystem;
class Game {
public:
    Game();
	~Game();

    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    SDL_Color getColorJudgment(const std::string& judgment);
    SDL_Color getColorCombo(const int combo);
    void loadChartFromFile(const std::string& path);

private:
    void checkNoteHit(int lane);

    SDL_Window* window;
    SDL_Renderer* renderer;

    Uint8 bgColorR, bgColorG, bgColorB;
    const int SCREEN_HEIGHT = 780;
    const int SCREEN_WIDTH = 600;
    const int Judgment_Line = SCREEN_HEIGHT - 100;

    bool isRunning;
    int score = 0;
    int combo = 0;
    int perfecthit = 0;
	int goodhit = 0;
	int badhit = 0;
	int misshit = 0;
	int maxCombo = 0;
	std::string currentJudgment;
	int comboDisplayTime;
    int timeJudgment = 0;
    int laneEffectTime[4];
    SDL_Color laneEffectColor[4];
    Menu* menu;
    AfterGame* afterGame;
	TTF_Font* fontScore;
	TTF_Font* fontJudgment;
    TTF_Font* fontCombo;
    ParticleSystem* particleSystem;

    std::vector<Note> notes;
    std::vector<NoteEvent> noteChart;
    size_t nextNoteIndex = 0;
    Uint32 startTimeMs = 0;
};

#endif
