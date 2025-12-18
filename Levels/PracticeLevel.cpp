#include "PracticeLevel.hpp"
#include <random>
#include <algorithm>
#include <iostream>

// --- Constructor ---
Practice::Practice(SDLInitializer& sdl, Window& window, EventManager& events,
                   int windowWidth, int windowHeight)
    : Stage(window, events, windowWidth, windowHeight),
      sdl_(sdl),
      player(30),
      playerRadius_(30),
      enemyAmount_(25),
      enemySpeed_(0),
      survivalTime_(0.0f),
      shieldTime_(0.0f),
      playerX_(0),
      playerY_(0),
      shieldOn_(true)
{
    // Nothing else to do here; real initialization happens in startGame()/restart().
}
// --- end: Constructor ---


// --- Primary interface ---
// Returns 0 on quit, 1 if a restart was triggered 
int Practice::startGame() {
    // --- Error Checking --- 
    if (!this->sdl_.sdlInitialized()) { return -1; }
    if (!this->sdl_.imgInitialized()) { return -1; }
    // --- end: Error Checking ---

    // --- Start Menu ---
    std::string lineGot;
    std::cout << "Input enemy amount: ";
    std::getline(std::cin, lineGot);
    this->enemyAmount_ = std::stoi(lineGot);

    std::cout << "Input enemy speed (0 for random): ";
    std::getline(std::cin, lineGot);
    this->enemySpeed_ = std::stoi(lineGot);
    // --- end: Start Menu ---

    // --- Initialize game state ---
    this->restart();

    // Run main loop from Stage
    return this->run();
}
// --- end: Primary interface ---


// --- Restart ---
// Resets enemies, survival time, and timing.
void Practice::restart() {
    // --- Player Initialization ---
    this->survivalTime_ = 0.0f;
    this->shieldTime_ = 3.0f; 
    this->shieldOn_ = true;
    // --- end: Player Initialization ---

    // --- Enemy Initialization ---
    this->enemies_.clear();
    this->enemies_.reserve(this->enemyAmount_);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(0, this->windowWidth_);
    std::uniform_int_distribution<> yDist(0, this->windowHeight_);
    std::uniform_int_distribution<> vDist(150, 300);

    for (int i = 0; i < this->enemyAmount_; i++) {
        int speedX = this->enemySpeed_ == 0 ? vDist(gen) : this->enemySpeed_;
        int speedY = this->enemySpeed_ == 0 ? vDist(gen) : this->enemySpeed_;

        this->enemies_.push_back(Enemy(
            xDist(gen), yDist(gen),
            75, 75,
            speedX, speedY
        ));
    }
    // --- end: Enemy Initialization ---
}
// --- end: Restart ---


// --- Stage hooks ---
void Practice::onEnter() {
    this->basicFont_ = sdl_.openFont("src/simple_font.ttf", 50);
}

void Practice::onExit() {
    TTF_CloseFont(this->basicFont_);
}

void Practice::handleEvents() {
    // Update player position from mouse
    this->playerX_ = this->events_.mouseX();
    this->playerY_ = this->events_.mouseY();
    this->player.updatePosition(this->playerX_, this->playerY_);

    if (this->events_.isKeyPressed(SDLK_c)) {
        this->startGame();
        return;
    }
    if (this->events_.isKeyPressed(SDLK_r)) {
        this->restart();
        return;
    }
}

void Practice::update(float dt) {
    // --- Update timers ---
    this->shieldTime_ -= dt;
    if (this->shieldTime_ <= 0.0f) {
        this->shieldTime_ = 0.0f;
        this->shieldOn_ = false;
    } else {
        this->shieldOn_ = true;
    }

    if (!this->shieldOn_) {
        this->survivalTime_ += dt;
    }
    // --- end: timers ---

    // --- Update enemies ---
    for (auto& enemy : this->enemies_) {
        enemy.update(dt, this->windowWidth_, this->windowHeight_);
    }
    // --- end: Update enemies ---

    // --- Check collisions ---
    if (!this->shieldOn_) {
        for (auto& enemy : this->enemies_) {
            if (Collision::circleRectCollision(this->playerX_, this->playerY_, this->playerRadius_, enemy.rect())) {
                int lostResult = this->lost();
                if (lostResult == 1) {
                    this->restart();
                } else {
                    return;
                }
                break;
            }
        }
    }
    // --- end: Check collisions ---
}

void Practice::render() {
    this->window_.beginFrame();

    // --- Render player ---
    this->player.render(this->window_.renderer());

    // --- Render enemies ---
    for (auto& enemy : this->enemies_) {
        enemy.render(this->window_.renderer());
    }

    // --- Render UI ---
    SDL_Color white {255, 255, 255, 255};
    SDL_Color green {6, 112, 0, 255};
    SDL_Color red {117, 20, 0, 255};

    if (!this->events_.pollEvents()) { return; }
    SDL_Rect scoreRect { this->windowWidth_ - 100, 35, 35, 35 };
    SDL_Rect shieldRect { this->windowWidth_ - 100, 85, 35, 35 };

    Texture::renderText(this->window_.renderer(), std::to_string(static_cast<int>(this->survivalTime_)) + "s", this->basicFont_, white, scoreRect);
    if (this->shieldOn_) {
        Texture::renderText(this->window_.renderer(), std::to_string(static_cast<int>(this->shieldTime_)) + "s", this->basicFont_, green, shieldRect);
    } else {
        Texture::renderText(this->window_.renderer(), std::to_string(static_cast<int>(this->shieldTime_)) + "s", this->basicFont_, red, shieldRect);
    }
    // --- end: UI ---

    this->window_.endFrame();
}
// --- end: Stage hooks ---


// --- Lost Screen ---
int Practice::lost() {
    SDL_Color white { 255, 255, 255, 255 };
    
    bool inLost = true;
    while (inLost) {
        if (!this->events_.pollEvents()) return 0;
        
        // Text rectangles
        SDL_Rect textRect { (this->windowWidth_ / 2) - 400, (this->windowHeight_ / 2) - 50, 800, 100 };
        SDL_Rect scoreRect { (this->windowWidth_ / 2) - 75, (this->windowHeight_ / 2) + 50, 150, 50 };

        if (this->events_.isKeyPressed(SDLK_r) || this->events_.isKeyPressed(SDLK_SPACE) || this->events_.isMousePressed(SDL_BUTTON_LEFT)) {
            this->events_.clearFrame();
            return 1;
        }
        if (this->events_.isKeyPressed(SDLK_ESCAPE)) {
            this->events_.clearFrame();
            return 0;
        }

        this->window_.beginFrame();
        Texture::renderText(this->window_.renderer(),
            "You Lost! Press R or Left-Click to Retry, ESC to Quit",
            this->basicFont_, white, textRect
        );
        Texture::renderText(this->window_.renderer(),
            "Time survived: " + std::to_string(static_cast<int>(this->survivalTime_)),
            this->basicFont_, white, scoreRect
        );
        this->window_.endFrame();
    }
    return 0;
}
// --- end: Lost Screen ---
