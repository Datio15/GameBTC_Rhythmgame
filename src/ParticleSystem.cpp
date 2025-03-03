#define _USE_MATH_DEFINES
#include "ParticleSystem.h"
#include <cmath>

ParticleSystem::ParticleSystem(SDL_Renderer* renderer, Game* game) : renderer(renderer), game(game) {
    std::random_device rd;
    rng = std::mt19937(rd());
}

void ParticleSystem::update() {
    for (auto it = particles.begin(); it != particles.end();) {
        it->update();
        if (it->isDead()) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ParticleSystem::render() {
    for (auto& particle : particles) {
        particle.render(renderer);
    }
}

void ParticleSystem::emitPerfectEffect(int x, int y) {
    SDL_Color color = game->getColorJudgment("Perfect");
    emitStarburst(x, y, color, 150);
    emitRingEffect(x, y, color, 100);
	emitRingEffect(x, y, {255,255,255,255}, 20);
}

void ParticleSystem::emitGoodEffect(int x, int y) {
    SDL_Color color = game->getColorJudgment("Good");
    emitStarburst(x, y, color, 30);
	emitRingEffect(x, y, color, 50);
}

void ParticleSystem::emitBadEffect(int x, int y) {
    SDL_Color color = game->getColorJudgment("Bad");
    emitBurst(x, y, color, 15);
	emitRingEffect(x, y, color, 30);
}

void ParticleSystem::emitMissEffect(int x, int y) {
    SDL_Color color = game->getColorJudgment("Miss");
    emitBurst(x, y, color, 10);
}

float ParticleSystem::randomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int ParticleSystem::randomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void ParticleSystem::emitStarburst(int x, int y, SDL_Color color, int count) {
    for (int i = 0; i < count; i++) {
        float angle = randomFloat(0, 2 * M_PI);
        float speed = randomFloat(1.0f, 3.0f);

        Particle p = { };
        p.x = static_cast<float>(x);
        p.y = static_cast<float>(y);
        p.vx = std::cos(angle) * speed;
        p.vy = std::sin(angle) * speed;
        p.size = randomInt(2, 4);
        p.r = color.r;
        p.g = color.g;
        p.b = color.b;
        p.a = color.a;
        p.maxLife = randomInt(30, 60);
        p.life = p.maxLife;

        particles.push_back(p);
    }
}

void ParticleSystem::emitRingEffect(int x, int y, SDL_Color color, int count) {
    float angleStep = 2 * M_PI / count;
    float initialRadius = 20.0f;
    float speed = 2.0f;

    for (int i = 0; i < count; i++) {
        float angle = i * angleStep;

        Particle p;
        p.x = static_cast<float>(x) + std::cos(angle) * initialRadius;
        p.y = static_cast<float>(y) + std::sin(angle) * initialRadius;
        p.vx = std::cos(angle) * speed;
        p.vy = std::sin(angle) * speed;
        p.size = 4;
        p.r = color.r;
        p.g = color.g;
        p.b = color.b;
        p.a = color.a;
        p.maxLife = 45;
        p.life = p.maxLife;

        particles.push_back(p);
    }
}

void ParticleSystem::emitBurst(int x, int y, SDL_Color color, int count) {
    for (int i = 0; i < count; i++) {
        float angle = randomFloat(0, 2 * M_PI);
        float speed = randomFloat(0.5f, 2.0f);

        Particle p= { };
        p.x = static_cast<float>(x);
        p.y = static_cast<float>(y);
        p.vx = std::cos(angle) * speed;
        p.vy = std::sin(angle) * speed;
        p.size = randomInt(2, 5);
        p.r = color.r;
        p.g = color.g;
        p.b = color.b;
        p.a = color.a;
        p.maxLife = randomInt(20, 40);
        p.life = p.maxLife;

        particles.push_back(p);
    }
}