#pragma once
// #include <iostream>
#include "../SDLLibrary/SDLLibrary.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

class Player {
public:
  enum class PlayerState { ALIVE, DEAD };

  Player(int sx, int sy, int radius, const std::string& color = "green")
      : currentX_(sx), currentY_(sy), radius_(radius), currentColor_(color),
        playerState_(PlayerState::ALIVE) {}

  void update(int mouseX, int mouseY);
  void render(SDL_Renderer* renderer);

  int radius();
  int currentX();
  int currentY();

  void setPlayerState(PlayerState state);
  PlayerState getPlayerState();

private:
  PlayerState playerState_;
  int currentX_;
  int currentY_;
  int radius_;
  std::string currentColor_;
};
