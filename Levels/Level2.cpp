#include "Level2.hpp"

Level createLevel2(int windowWidth, int windowHeight) {
  Level level;
  level.canKillEnemies = false;
  level.enemyCount = 50;
  level.minSpeed = 100.0f;
  level.maxSpeed = 115.0f;
  level.walls = {{0, 0, 320, 495},       // Top wall left tunnel
                 {0, 585, 320, 495},     // Bottom wall left tunnel
                 {760, 340, 400, 400},   // Middle obstacle
                 {1600, 0, 320, 495},    // Top wall right tunnel
                 {1600, 585, 320, 495}}; // Bottom wall right tunnel
  level.spawnBounds = {320, 0, 1280, 1080};
  level.playerSpawnX = 160;
  level.playerSpawnY = 540;
  level.limitingWall.first = 320;
  level.limitingWall.second = 0;
  return level;
}
