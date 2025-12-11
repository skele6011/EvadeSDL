#include "Player.hpp"

Player::Player(int r) : radius_(r), x_(0), y_(0) {}

void Player::updatePosition(int mousex, int mousey) {
    x_ = mousex;
    y_ = mousey;
}

void Player::render(SDL_Renderer* renderer) {
    // Layer ratios
    float coreRatio = 0.5f;    // 50% of total radius
    float middleRatio = 0.25f; // 25% of total radius
    float outerRatio = 0.25f;  // 25% of total radius
    (void)outerRatio;

    // Compute layer radii
    int outerRadius = radius_; // full radius
    int middleRadius = static_cast<int>(std::round(radius_ * (coreRatio + middleRatio))); // 50% + 25% = 75%
    int coreRadius   = static_cast<int>(std::round(radius_ * coreRatio)); // 50%

    // Enable blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Outer circle - subtle shadow
    filledCircleRGBA(renderer, x_, y_, outerRadius, 120, 10, 120, 180);

    // Middle circle - brighter
    filledCircleRGBA(renderer, x_, y_, middleRadius, 180, 60, 180, 200);

    // Core circle - highlight
    filledCircleRGBA(renderer, x_, y_, coreRadius, 255, 150, 255, 255);


    // ----------------------
    /*
    // Draw three layers of alpha
    filledCircleRGBA(renderer, x_, y_, radius_, 153, 102, 204, 102);
    filledCircleRGBA(renderer, x_, y_, static_cast<int>(std::round(radius_ * 0.67)), 102, 51, 204, 255);
    filledCircleRGBA(renderer, x_, y_, static_cast<int>(std::round(radius_ * 0.33)), 212, 163, 255, 102);
    */
}
