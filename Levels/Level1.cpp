#include "Level1.hpp"

Level createLevel1(int windowWidth, int windowHeight, int playerSpawnX,
                   int playerSpawnY) {
  Level level;
  level.canKillEnemies = true;
  level.enemyCount = 50;
  level.minSpeed = 150.0f;
  level.maxSpeed = 165.0f;
  level.walls = {};
  level.spawnBounds = {0, 0, windowWidth, windowHeight};
  level.playerSpawnX = playerSpawnX;
  level.playerSpawnY = playerSpawnY;
  return level;
}
