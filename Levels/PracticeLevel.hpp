#pragma once
#include "Stage.hpp"
#include "../Utils/Enemy.hpp"
#include "../Utils/Player.hpp"
#include "../SDLLibrary/SDLLibrary.h"
#include <vector>
#include <string>

// --- Practice level ---
// Survival-style practice level.
// Holds player, enemies, and per-level state.
// --- end: Practice level ---
class Practice : public Stage {
private:
    SDLInitializer& sdl_;  
    Player player;

    // --- Game State Below ---
    int playerRadius_;
    std::vector<Enemy> enemies_;
    int enemyAmount_;
    int enemySpeed_;
    float survivalTime_;
    float shieldTime_;
    int playerX_;
    int playerY_;
    bool shieldOn_;
    TTF_Font* basicFont_;
    // --- end: Game State --- 

public:
    // --- Constructor ---
    Practice(SDLInitializer& sdl, Window& window, EventManager& events,
             int windowWidth = 1920, int windowHeight = 1080);
    // --- end: Constructor ---

    // --- Primary interface (implements Stage) ---
    int startGame(); // Initializes and calls Stage::run
    // --- end: Primary interface ---

protected:
    // --- Stage hooks ---
    void handleEvents() override;
    void update(float dt) override;
    void render() override;
    void onEnter() override;
    void onExit() override;
    // --- end: Stage hooks ---

private:
    void restart();            // Resets enemies, shield, and timing
    int lost();                // Lost screen + retry logic
};
