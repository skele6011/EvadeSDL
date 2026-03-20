#include "enemy.hpp"
#include <SDL2/SDL_render.h>

// Need to make collisions work with wall
void Enemy::update(int windowWidth, int windowHeight, float dt) {
  this->currentX_ += this->velocityX_ * dt;
  this->currentY_ += this->velocityY_ * dt;

  // Right wall
  if (currentX_ + rect_.w >= windowWidth) {
    currentX_ = windowWidth - rect_.w; // clamp
    velocityX_ *= -1;
  }

  // Left wall
  if (currentX_ <= 0) {
    currentX_ = 0;
    velocityX_ *= -1;
  }

  // Bottom wall
  if (currentY_ + rect_.h >= windowHeight) {
    currentY_ = windowHeight - rect_.h;
    velocityY_ *= -1;
  }

  // Top wall
  if (currentY_ <= 0) {
    currentY_ = 0;
    velocityY_ *= -1;
  }

  this->rect_.x = this->currentX_;
  this->rect_.y = this->currentY_;
}

SDL_Rect Enemy::getRect() { return this->rect_; }

void Enemy::render(SDL_Renderer* renderer) {
  boxRGBA(renderer, this->rect_.x, this->rect_.y, this->rect_.x + this->rect_.w,
          this->rect_.y + this->rect_.h, 200, 10, 10, 255);
}
