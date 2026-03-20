#include "Entity/enemy.hpp"
#include "Entity/player.hpp"
#include "SDLLibrary/SDLLibrary.h"
#include "SDLLibrary/Utils/Collision.hpp"
#include <SDL2/SDL.h>
// #include <iostream>
#include <SDL2/SDL_video.h>
#include <random>
// #include <string>
#include <vector>
enum class GameState { MENU, PLAYING, GAME_OVER };

void gamePlay(Player& player, std::vector<Enemy>& enemies, EventManager& em,
              SDL_Renderer* renderer, int width, int height,
              GameState& gameState, Uint32 spawnTime) {
  if (gameState == GameState::PLAYING) {
    player.update(em.mouseX(), em.mouseY());
    player.render(renderer);

    // Give 3 second shield
    bool shieldOn = (SDL_GetTicks() - spawnTime) < 3000;

    // Setup enemies & Collision
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
      // Dereference first [(*it)], then update method on that class
      // [.update()]
      (*it).update(width, height);
      (*it).render(renderer);

      bool collided =
          Collision::circleRectCollision(player.currentX(), player.currentY(),
                                         player.radius(), (*it).getRect());
      // If collided, dead.
      if (collided && !shieldOn) {
        player.setPlayerState(Player::PlayerState::DEAD);
        gameState =
            GameState::MENU; // Go to menu for now (change to GAME_OVER later)
      }
    }
  }
}

void gameMenu(EventManager& em, SDL_Renderer* renderer, TTF_Font* fontLarge,
              TTF_Font* fontSmall, GameState& gameState, int windowWidth,
              int windowHeight, Uint32& spawnTime) {
  if (gameState == GameState::MENU) {
    SDL_Color red = {220, 50, 50, 255};
    SDL_Color gray = {180, 180, 180, 255};

    // Title
    int tw, th;
    TTF_SizeText(fontLarge, "Evade", &tw, &th);
    SDL_Rect titleRect = {(windowWidth - tw) / 2, windowHeight / 2 - 100, tw,
                          th};
    Texture::renderText(renderer, "Evade", fontLarge, red, titleRect);

    // Subtitle
    int sw, sh;
    TTF_SizeText(fontSmall, "Press SPACE to play", &sw, &sh);
    SDL_Rect subRect = {(windowWidth - sw) / 2, windowHeight / 2 + 20, sw, sh};
    Texture::renderText(renderer, "Press SPACE to play", fontSmall, gray,
                        subRect);

    if (em.isKeyPressed(SDLK_SPACE)) {
      spawnTime = SDL_GetTicks();
      gameState = GameState::PLAYING;
    }
  }
}

int main() {
  SDLInitializer Initializer(SDL_INIT_VIDEO | SDL_INIT_AUDIO,
                             IMG_INIT_PNG); // Image not used

  TTF_Font* fontSmall =
      Initializer.openFont("dejavu-sans/DejaVuSans-Bold.ttf", 36);
  TTF_Font* fontLarge =
      Initializer.openFont("dejavu-sans/DejaVuSans-Bold.ttf", 144);

  Window window("Window", 1048, 1048);
  int swidth, sheight; // Start width/height
  SDL_GetWindowSize(window.window(), &swidth, &sheight);

  SDL_Renderer* renderer = window.renderer();

  EventManager em(window.window(), false);

  Player player(500, 500, 15);
  GameState gameState = GameState::MENU; // Starts at game for now
  Uint32 spawnTime = SDL_GetTicks();

  // --- Create enemies ---
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrX(0, swidth);
  std::uniform_int_distribution<> distrY(0, sheight);

  std::vector<Enemy> enemies;
  for (int i = 0; i < 50; i++) {
    enemies.emplace_back(distrX(gen), distrY(gen), 64, 64, "green", 1.5f,
                         1.65f);
  }
  // --- end: Create enemies ---

  bool running = true;
  while (running) {
    running = em.pollEvents();

    // Doesn't allow window-resize cheating
    if (gameState == GameState::PLAYING) {
      SDL_SetWindowResizable(window.window(), SDL_FALSE);
    } else {
      SDL_SetWindowResizable(window.window(), SDL_TRUE);
    }

    window.beginFrame();
    // If playing, this will run
    gamePlay(player, enemies, em, renderer, em.windowWidth(), em.windowHeight(),
             gameState, spawnTime);
    // If menu
    gameMenu(em, renderer, fontLarge, fontSmall, gameState, em.windowWidth(),
             em.windowHeight(), spawnTime);

    window.endFrame();

    // std::cout << width << std::endl << height << std::endl;
    SDL_Delay(5); // ~15 = ~60FPS
  }

  return 0;
}
