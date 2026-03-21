#include "Level2.hpp"

Level createLevel2(int windowWidth, int windowHeight) {
  Level level;
  level.canKillEnemies = false;
  level.enemyCount = 50;
  level.minSpeed = 100.0f;
  level.maxSpeed = 115.0f;
  level.walls = {{760, 340, 400, 400}};
  level.spawnBounds = {320, 0, 1280, 1080};
  level.playerSpawnX = windowWidth / 2;
  level.playerSpawnY = windowHeight / 2;
  return level;
}
