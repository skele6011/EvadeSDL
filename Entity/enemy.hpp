#include "../SDLLibrary/SDLLibrary.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Enemy {
private:
  int currentX_;
  int currentY_;
  float velocityX_;
  float velocityY_;
  std::string currentColor_; // Might use later
  SDL_Rect rect_;
  int width_;
  int height_;

public:
  Enemy(int sx, int sy, int width, int height, const std::string& color = "red",
        float vx = 5.0f, float vy = 7.0f)
      : currentX_(sx), currentY_(sy), width_(width), height_(height),
        currentColor_(color), rect_{sx, sy, width, height}, velocityX_(vx),
        velocityY_(vy) {} // Default values for velocity here.

  void update(int windowWidth, int windowHeight);
  void render(SDL_Renderer* renderer);

  void setColor(const std::string& color);

  SDL_Rect getRect();
};
