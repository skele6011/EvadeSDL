#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(int x, int y, int w, int h, int velX, int velY) {
    this->rect_ = {x, y, w, h};
    this->vx_ = velX;
    this->vy_ = velY;
    this->fx_ = x;
    this->fy_ = y;
}

void Enemy::update(float dt, int windowWidth, int windowHeight) {
    this->fx_ += this->vx_ * dt;
    this->fy_ += this->vy_ * dt;

    // Simple wall bounce
    if (this->fx_ < 0) { this->rect_.x = 0; this->vx_ = -this->vx_; }
    if (this->fx_ + this->rect_.w > windowWidth) { rect_.x = windowWidth - rect_.w; this->vx_ = -this->vx_; }
    if (this->fy_ < 0) { rect_.y = 0; this->vy_ = -this->vy_; }
    if (this->fy_ + rect_.h > windowHeight) { rect_.y = windowHeight - rect_.h; this->vy_ = -this->vy_; }
    
    this->rect_.x = static_cast<int>(this->fx_);
    this->rect_.y = static_cast<int>(this->fy_);
}

void Enemy::render(SDL_Renderer* renderer) {
    // Total rectangle
    int totalW = this->rect_.w;
    int totalH = this->rect_.h;

    // Layer ratios
    float coreRatio = 0.5f;   // 50% of total size
    float middleRatio = 0.25f; // 25% of total size
    float outerRatio = 0.25f;  // 25% of total size
    (void)outerRatio;

    // Compute layer sizes
    int coreW = (int)(totalW * coreRatio);
    int coreH = (int)(totalH * coreRatio);

    int middleW = (int)(totalW * (coreRatio + middleRatio));
    int middleH = (int)(totalH * (coreRatio + middleRatio));

    int outerW = totalW; // full size
    int outerH = totalH;

    // Center coordinates
    int centerX = this->rect_.x + this->rect_.w / 2;
    int centerY = this->rect_.y + this->rect_.h / 2;

    // Define rectangles
    SDL_Rect outer = {
        centerX - outerW / 2,
        centerY - outerH / 2,
        outerW,
        outerH
    };

    SDL_Rect middle = {
        centerX - middleW / 2,
        centerY - middleH / 2,
        middleW,
        middleH
    };

    SDL_Rect core = {
        centerX - coreW / 2,
        centerY - coreH / 2,
        coreW,
        coreH
    };

    // Enable blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Outer rectangle - subtle shadow
    SDL_SetRenderDrawColor(renderer, 120, 10, 10, 180);
    SDL_RenderFillRect(renderer, &outer);

    // Middle rectangle - slightly brighter
    SDL_SetRenderDrawColor(renderer, 180, 40, 40, 200);
    SDL_RenderFillRect(renderer, &middle);

    // Core rectangle - bright highlight
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    SDL_RenderFillRect(renderer, &core);



    // ---------------------
    /*
    // three-layer rectangle
    SDL_Rect outer = {rect_.x - 5, rect_.y - 5, rect_.w + 10, rect_.h + 10};
    SDL_Rect middle = {rect_.x - 2, rect_.y - 2, rect_.w + 4, rect_.h + 4};

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 163, 5, 5, 102);
    SDL_RenderFillRect(renderer, &outer);

    SDL_SetRenderDrawColor(renderer, 115, 3, 3, 218);
    SDL_RenderFillRect(renderer, &middle);

    SDL_SetRenderDrawColor(renderer, 255, 82, 82, 255);
    SDL_RenderFillRect(renderer, &rect_);
    */
}