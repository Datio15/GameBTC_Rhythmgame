#include "Game.h"
#include "TextureManager.h"
#include <vector>
#include "Note.h"

std::vector<Note> notes; // Lưu danh sách nốt

using namespace std;
void randNote() {
	int lane = rand() % 4;

	notes.emplace_back(Note(lane * 150, 0, 150, 20, 5));
}
Game:: Game(){}
Game:: ~Game() {}
void Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window)
        {
            cout << "Window created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, bgColorB,bgColorG,bgColorR,255);
            cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }
}
void Game::handleEvents() {
	InputHandler::Instance()->update();
    if (InputHandler::Instance()->isKeyPressed(SDLK_a)) {  // Giữ phím A
        for (auto it = notes.begin(); it != notes.end(); ) {
            int noteY = it->getY() + 20;

            if (noteY >= 480 && noteY <= 520) {  // Perfect rộng hơn
                cout << "Perfect" << endl;
                it = notes.erase(it);  // Xóa nốt khi đánh trúng
            }
            else if (noteY >= 521 && noteY <= 540) {
                cout << "Good" << endl;
                it = notes.erase(it);
            }
            else if (noteY >= 541 && noteY <= 560) {
                cout << "Bad" << endl;
                it = notes.erase(it);
            }
            else {
				cout << "Miss" << endl;
                ++it;  // Không xóa thì tiếp tục duyệt phần tử tiếp theo
            }
        }
    }
    if (InputHandler::Instance()->isKeyPressed(SDLK_s)) {
        for (auto it = notes.begin(); it != notes.end(); ) {
            int noteY = it->getY() + 20;

            if (noteY >= 480 && noteY <= 520) {  // Perfect rộng hơn
                cout << "Perfect" << endl;
                it = notes.erase(it);  // Xóa nốt khi đánh trúng
            }
            else if (noteY >= 521 && noteY <= 540) {
                cout << "Good" << endl;
                it = notes.erase(it);
            }
            else if (noteY >= 541 && noteY <= 560) {
                cout << "Bad" << endl;
                it = notes.erase(it);
            }
            else {
                cout << "Miss" << endl;
                ++it;  // Không xóa thì tiếp tục duyệt phần tử tiếp theo
            }
        }
    }
    if (InputHandler::Instance()->isKeyPressed(SDLK_d)) {
        for (auto it = notes.begin(); it != notes.end(); ) {
            int noteY = it->getY() + 20;

            if (noteY >= 480 && noteY <= 520) {  // Perfect rộng hơn
                cout << "Perfect" << endl;
                it = notes.erase(it);  // Xóa nốt khi đánh trúng
            }
            else if (noteY >= 521 && noteY <= 540) {
                cout << "Good" << endl;
                it = notes.erase(it);
            }
            else if (noteY >= 541 && noteY <= 560) {
                cout << "Bad" << endl;
                it = notes.erase(it);
            }
            else {
                cout << "Miss" << endl;
                ++it;  // Không xóa thì tiếp tục duyệt phần tử tiếp theo
            }
        }
    }
    if (InputHandler::Instance()->isKeyPressed(SDLK_f)) {
        for (auto it = notes.begin(); it != notes.end(); ) {
            int noteY = it->getY() + 20;

            if (noteY >= 480 && noteY <= 520) {  // Perfect rộng hơn
                cout << "Perfect" << endl;
                it = notes.erase(it);  // Xóa nốt khi đánh trúng
            }
            else if (noteY >= 521 && noteY <= 540) {
                cout << "Good" << endl;
                it = notes.erase(it);
            }
            else if (noteY >= 541 && noteY <= 560) {
                cout << "Bad" << endl;
                it = notes.erase(it);
            }
            else {
                ++it;  // Không xóa thì tiếp tục duyệt phần tử tiếp theo
            }
        }
    }
}

void Game::update() {
    if (rand() % 100 == 0) {
		randNote();
    }
    // Cập nhật nốt nhạc
    for (auto& note : notes) {
        note.update();
    }

    // Xóa nốt rơi ra khỏi màn hình
    notes.erase(std::remove_if(notes.begin(), notes.end(),
        [](Note& n) { return n.isOffScreen(); }), notes.end());

}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, bgColorB, bgColorG, bgColorR, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 1; i <= 3; i++) {
        SDL_RenderDrawLine(renderer, i * 150, 0, i * 150, 600);
    }
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Vẽ tất cả các nốt nhạc
    for (auto& note : notes) {
        note.render(renderer);
    }

	TextureManager::Instance()->load("Anime Girl","D:/rhygame/drum/assets/Anime.png", renderer);
    TextureManager::Instance()->draw("Anime Girl", 0, 500, 150, 100, renderer);
    TextureManager::Instance()->draw("Anime Girl", 150, 500, 150, 100, renderer);
    TextureManager::Instance()->draw("Anime Girl", 300, 500, 150, 100, renderer);
    TextureManager::Instance()->draw("Anime Girl", 450, 500, 150, 100, renderer);
    SDL_RenderDrawLine(renderer, 0, 500, 600, 500);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
	//TextureManager::Instance()->clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
