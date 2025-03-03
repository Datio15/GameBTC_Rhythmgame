#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SDL.h>
#include <vector>
#include <random>
#include "Game.h"

class Game;
struct Particle {
    float x, y;
    float vx, vy;
    int size;
    Uint8 r, g, b, a;
    int life;
    int maxLife;

    void update() {
        x += vx;
        y += vy;
        life--;
        a = static_cast<Uint8>(255 * (static_cast<float>(life) / maxLife));
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_Rect rect = {
            static_cast<int>(x - size / 2),
            static_cast<int>(y - size / 2),
            size, size
        };
        SDL_RenderFillRect(renderer, &rect);
    }

    bool isDead() const {
        return life <= 0;
    }
};

class ParticleSystem {
public:
    ParticleSystem(SDL_Renderer* renderer, Game* game);
    void update();
    void render();
    void emitPerfectEffect(int x, int y);
    void emitGoodEffect(int x, int y);
    void emitBadEffect(int x, int y);
    void emitMissEffect(int x, int y);

private:
    SDL_Renderer* renderer;
    Game* game; // Con trỏ tới Game để truy cập getColorJudgment
    std::vector<Particle> particles;
    std::mt19937 rng;

    float randomFloat(float min, float max);
    int randomInt(int min, int max);
    void emitStarburst(int x, int y, SDL_Color color, int count);
    void emitRingEffect(int x, int y, SDL_Color color, int count);
    void emitBurst(int x, int y, SDL_Color color, int count);
};
#endif // PARTICLESYSTEM_H