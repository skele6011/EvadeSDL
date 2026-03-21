#pragma once
#include "Level.hpp"
#include <SDL2/SDL.h>

#include <iomanip> // IWYU pragma: keep
#include <random>  // IWYU pragma: keep
#include <sstream> // IWYU pragma: keep
#include <string>  // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

class LevelOne : public LevelBase {
public:
  LevelOne(Player& player, EventManager& em, TTF_Font* smallFont,
           Uint32 spawnTime, std::mt19937& gen);

  LevelResult update(float dt) override;
  void render(SDL_Renderer* renderer) override;

private:
  bool shieldOn_ = false;
  float survivalTime_ = 0.0f;
};
