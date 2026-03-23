#include "Editor.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

Editor::Editor(EventManager& em, TTF_Font* smallFont)
    : em_(em), smallFont_(smallFont), currentType_({100, 100, 100, 255}) {}

bool Editor::update(float dt) {
  // Color/Type picker
  SDL_Color red = {255, 20, 20, 150};
  SDL_Color green = {20, 255, 20, 150};
  SDL_Color gray = {100, 100, 100, 150};
  if (this->em_.isKeyPressed(SDLK_g)) {
    this->currentType_ = green;
  }
  if (this->em_.isKeyPressed(SDLK_r)) {
    this->currentType_ = red;
  }
  if (this->em_.isKeyPressed(SDLK_w)) {
    this->currentType_ = gray;
  }

  bool leftHeld = this->em_.mouseButtons() & SDL_BUTTON(SDL_BUTTON_LEFT);
  if (leftHeld && !this->isDragging_) {
    this->isDragging_ = true;
    this->dragStart_ = {this->em_.mouseX(), this->em_.mouseY()};
  }

  if (this->isDragging_ && !leftHeld) {
    // Released - create the rect
    int x = std::min(dragStart_.x, this->em_.mouseX());
    int y = std::min(dragStart_.y, this->em_.mouseY());
    int w = std::abs(this->em_.mouseX() - dragStart_.x);
    int h = std::abs(this->em_.mouseY() - dragStart_.y);
    // snap to 5px grid
    x = (x / 5) * 5;
    y = (y / 5) * 5;
    w = (w / 5) * 5;
    h = (h / 5) * 5;
    this->wallsViewer_.push_back({x, y, w, h}); // for now always adds as wall

    // Set walls for screen resizing
    this->walls_.push_back({(float)x / this->em_.windowWidth(),
                            (float)y / this->em_.windowHeight(),
                            (float)w / this->em_.windowWidth(),
                            (float)h / this->em_.windowHeight()});

    this->isDragging_ = false;
  }

  // False = Exit
  // True = Continue
  if (this->em_.isKeyPressed(SDLK_ESCAPE)) {
    return false;
  }
  return true;
}

// Draw the normal int position from wallsViewer_
// Means you cannot change window size WHILE editing.
void Editor::render(SDL_Renderer* renderer) {
  // Setup Type Viewer
  SDL_Rect typeViewer{this->em_.windowWidth() - 50, 5, 45, 45};
  boxRGBA(renderer, typeViewer.x, typeViewer.y, typeViewer.x + typeViewer.w,
          typeViewer.y + typeViewer.h, this->currentType_.r,
          this->currentType_.g, this->currentType_.b, this->currentType_.a);

  if (this->isDragging_) {
    int x = std::min(dragStart_.x, this->em_.mouseX());
    int y = std::min(dragStart_.y, this->em_.mouseY());
    int w = std::abs(this->em_.mouseX() - dragStart_.x);
    int h = std::abs(this->em_.mouseY() - dragStart_.y);

    boxRGBA(renderer, x, y, x + w, y + h, this->currentType_.r,
            this->currentType_.g, this->currentType_.b,
            100); // Semi-transparent for preview
  }

  // Render walls After Drawn
  for (const auto& wall : this->wallsViewer_) {
    boxRGBA(renderer, wall.x, wall.y, wall.x + wall.w, wall.y + wall.h,
            this->currentType_.r, this->currentType_.g, this->currentType_.b,
            255);
  }
}
