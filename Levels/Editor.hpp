#include "../SDLLibrary/SDLLibrary.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

#include <vector>

class Editor {
public:
  Editor(EventManager& em, TTF_Font* smallFont);

  bool update(float dt); // Returns false if user decides to exist editor
  void render(SDL_Renderer* renderer);

private:
  SDL_Color currentType_;
  EventManager& em_;
  TTF_Font* smallFont_;

  std::vector<SDL_Rect> walls_;
  std::vector<SDL_Rect> spawnBounds_;
  SDL_Rect limitingWall_;

  bool isDragging_ = false;
  SDL_Point dragStart_;
};
