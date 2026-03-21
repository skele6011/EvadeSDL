#include "player.hpp"

void Player::update(int mouseX, int mouseY) {
  this->currentX_ = mouseX;
  this->currentY_ = mouseY;
}

void Player::render(SDL_Renderer* renderer) {
  filledCircleRGBA(renderer, this->currentX_, this->currentY_, this->radius_,
                   10, 200, 10, 255);
}

int Player::currentX() { return this->currentX_; }
int Player::currentY() { return this->currentY_; }
int Player::radius() { return this->radius_; }

void Player::setPlayerX(int x) { this->currentX_ = x; }
void Player::setPlayerY(int y) { this->currentX_ = y; }

void Player::setPlayerState(Player::PlayerState state) {
  this->playerState_ = state;
}
Player::PlayerState Player::getPlayerState() { return this->playerState_; }
