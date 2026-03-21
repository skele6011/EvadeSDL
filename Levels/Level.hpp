#pragma once
#include <SDL2/SDL.h>
#include <utility>
#include <vector>

struct Level {
  bool canKillEnemies;
  std::vector<SDL_Rect> walls;
  int enemyCount;
  float minSpeed, maxSpeed;
  SDL_Rect spawnBounds;
  int playerSpawnX, playerSpawnY;
  std::pair<int, int> limitingWall;
};
