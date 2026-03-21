#include "Level1.hpp"
#include "Level.hpp"

LevelOne::LevelOne(Player& player, EventManager& em, TTF_Font* smallFont,
                   Uint32 spawnTime, std::mt19937& gen)
    : LevelBase(player, em, smallFont, spawnTime, gen) {
  data.canKillEnemies = true;
  data.enemyCount = 100;
  data.minSpeed = 150.0f;
  data.maxSpeed = 165.0f;
  data.spawnBounds = {0, 0, em.windowWidth(), em.windowHeight()};

  std::uniform_int_distribution<> distrX(0, em.windowWidth());
  std::uniform_int_distribution<> distrY(0, em.windowHeight());
  for (int i = 0; i < data.enemyCount; i++) {
    enemies_.emplace_back(distrX(gen), distrY(gen), 64, 64, "red",
                          data.minSpeed, data.maxSpeed);
  }
}

LevelResult LevelOne::update(float dt) {
  this->player_.update(this->em_.mouseX(), this->em_.mouseY());

  // Give 3 second shield
  this->shieldOn_ = (SDL_GetTicks() - this->spawnTime_) < 3000;

  // Setup enemies & Collision
  for (auto it = this->enemies_.begin(); it != this->enemies_.end(); ++it) {
    // Dereference first [(*it)], then update method on that class
    // [.update()]
    (*it).update(this->em_.windowWidth(), this->em_.windowHeight(), dt);

    bool collided = Collision::circleRectCollision(
        this->player_.currentX(), this->player_.currentY(),
        this->player_.radius(), (*it).getRect());
    // If collided, dead.
    if (collided && !this->shieldOn_) {
      this->player_.setPlayerState(Player::PlayerState::DEAD);
      return LevelResult::DIED;
    }
  }

  return LevelResult::NONE; // Can't win for now
}

void LevelOne::render(SDL_Renderer* renderer) {
  // Render player and enemies
  this->player_.render(renderer);
  for (auto it = this->enemies_.begin(); it != this->enemies_.end(); ++it) {
    (*it).render(renderer);
  }

  // Timer
  float survivalTime = (SDL_GetTicks() - this->spawnTime_ - 3000) / 1000.0f;
  // Display timer
  int timerWidth, timerHeight;
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1) << survivalTime << "s";
  std::string timerText = oss.str();
  TTF_SizeText(this->smallFont_, "555.5s", &timerWidth, &timerHeight);
  SDL_Rect timerRect = {(this->em_.windowWidth() - timerWidth) / 2, 20,
                        timerWidth, timerHeight};
  SDL_Color red = {220, 50, 50, 255};
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color timerColor = this->shieldOn_ ? green : red;
  timerText = this->shieldOn_ ? "0.0s" : timerText;
  Texture::renderText(renderer, timerText, this->smallFont_, timerColor,
                      timerRect);
}
