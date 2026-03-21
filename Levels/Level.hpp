#pragma once
#include <SDL2/SDL.h>
#include <random>
#include <utility>
#include <vector>

#include "../Entity/enemy.hpp"
#include "../Entity/player.hpp"

enum class LevelResult { NONE, DIED, WON, PAUSED };

struct Level {
  bool canKillEnemies;
  std::vector<SDL_Rect> walls;
  int enemyCount;
  float minSpeed, maxSpeed;
  SDL_Rect spawnBounds;
  int playerSpawnX, playerSpawnY;
  std::pair<int, int> limitingWall;
};

class LevelBase {
public:
  LevelBase(Player& player, EventManager& em, TTF_Font* smallFont,
            Uint32 spawnTime, std::mt19937& gen)
      : player_(player), em_(em), smallFont_(smallFont), spawnTime_(spawnTime),
        gen_(gen) {}
  virtual LevelResult update(float dt) = 0;
  virtual void render(SDL_Renderer* renderer) = 0;
  Level data;
  virtual ~LevelBase() {
  }; // To ensure C++ generates a destructor gets called for the subclasses

protected:
  Player& player_;
  std::vector<Enemy> enemies_;
  EventManager& em_;
  TTF_Font* smallFont_;
  Uint32 spawnTime_;
  std::mt19937& gen_;
};
