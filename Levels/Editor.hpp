#include "../SDLLibrary/SDLLibrary.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

#include <utility>
#include <vector>

struct NormalizedRect {
  float x, y, w, h;
};

class Editor {
public:
  Editor(EventManager& em, TTF_Font* smallFont);

  bool update(float dt); // Returns false if user decides to exist editor
  void render(SDL_Renderer* renderer);

private:
  SDL_Color currentType_;
  EventManager& em_;
  TTF_Font* smallFont_;

  SDL_Color red_ = {255, 20, 20, 150};
  SDL_Color green_ = {20, 255, 20, 150};
  SDL_Color gray_ = {100, 100, 100, 150};

  std::vector<SDL_Rect> wallsViewer_;
  std::vector<std::pair<SDL_Color, NormalizedRect>> walls_;
  std::vector<SDL_Rect> spawnBounds_;
  SDL_Rect limitingWall_;

  bool isDragging_ = false;
  SDL_Point dragStart_;
};
