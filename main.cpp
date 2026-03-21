#include "Entity/enemy.hpp" // IWYU pragma: keep
#include "Entity/player.hpp"

#include "Levels/Level1.hpp"
#include "Levels/Level2.hpp"

#include "Levels/Editor.hpp"

#include "SDLLibrary/SDLLibrary.h"
#include "SDLLibrary/Utils/Collision.hpp" // IWYU pragma: keep

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <iostream> // IWYU pragma: keep

#include <iomanip> // IWYU pragma: keep
#include <random>
#include <sstream> // IWYU pragma: keep
#include <string>
#include <vector> // IWYU pragma: keep

enum class GameState { MENU, PLAYING, GAME_OVER, EDITOR };

void gameMenu(EventManager& em, SDL_Renderer* renderer, TTF_Font* fontLarge,
              TTF_Font* smallFont, GameState& gameState, int windowWidth,
              int windowHeight, Uint32& spawnTime) {
  SDL_Color red = {220, 50, 50, 255};
  SDL_Color gray = {180, 180, 180, 255};

  // Title
  int tw, th;
  TTF_SizeText(fontLarge, "Evade", &tw, &th);
  SDL_Rect titleRect = {(windowWidth - tw) / 2, windowHeight / 2 - 100, tw, th};
  Texture::renderText(renderer, "Evade", fontLarge, red, titleRect);

  // Subtitle
  int sw, sh;
  TTF_SizeText(smallFont, "Press SPACE to play", &sw, &sh);
  SDL_Rect subRect = {(windowWidth - sw) / 2, windowHeight / 2 + 20, sw, sh};
  Texture::renderText(renderer, "Press SPACE to play", smallFont, gray,
                      subRect);

  if (em.isKeyPressed(SDLK_SPACE)) {
    spawnTime = SDL_GetTicks();
    gameState = GameState::PLAYING;
  }
}

int main() {
  SDLInitializer Initializer(SDL_INIT_VIDEO | SDL_INIT_AUDIO,
                             IMG_INIT_PNG); // Image not used

  TTF_Font* smallFont =
      Initializer.openFont("dejavu-sans/DejaVuSans-Bold.ttf", 36);
  TTF_Font* fontLarge =
      Initializer.openFont("dejavu-sans/DejaVuSans-Bold.ttf", 144);

  Window window("Window", 1920, 1080);

  SDL_Renderer* renderer = window.renderer();

  EventManager em(window.window(), false);

  Player player(em.windowWidth() / 2, em.windowHeight() / 2, 15);
  GameState gameState = GameState::MENU;
  Uint32 spawnTime = SDL_GetTicks();

  std::random_device rd;
  std::mt19937 gen(rd());

  Editor editor(em, smallFont);
  LevelBase* currentLevelObj =
      new LevelOne(player, em, smallFont, spawnTime, gen);

  Uint32 lastFrame = SDL_GetTicks();
  bool running = true;
  while (running) {
    running = em.pollEvents();
    Uint32 frameStart = SDL_GetTicks();
    float dt = (frameStart - lastFrame) / 1000.0f;

    // Doesn't allow window-resize cheating
    if (gameState == GameState::PLAYING) {
      SDL_SetWindowResizable(window.window(), SDL_FALSE);
    } else {
      SDL_SetWindowResizable(window.window(), SDL_TRUE);
    }

    window.beginFrame();

    if (gameState == GameState::PLAYING) {
      LevelResult result = currentLevelObj->update(dt);
      currentLevelObj->render(renderer);
      if (result == LevelResult::DIED) {
        gameState = GameState::MENU; // No game-over screen yet
      }
    }

    if (gameState == GameState::EDITOR) {
      bool continueEditor = editor.update(dt);
      editor.render(renderer);
      if (!continueEditor) {
        gameState = GameState::MENU;
      }
    }

    if (gameState == GameState::MENU) {
      gameMenu(em, renderer, fontLarge, smallFont, gameState, em.windowWidth(),
               em.windowHeight(), spawnTime);
    }

    // For testing - Editor
    if (em.isKeyPressed(SDLK_e) && em.isKeyDown(SDLK_LSHIFT)) {
      SDL_ShowCursor(SDL_ENABLE);
      gameState = GameState::EDITOR;
    }

    window.endFrame();

    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < (1000 / 240)) {
      SDL_Delay((1000 / 240) - frameTime);
    }
    lastFrame = frameStart;
  }

  return 0;
}
