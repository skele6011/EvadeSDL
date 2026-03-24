#include "Editor.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

Editor::Editor(EventManager& em, TTF_Font* smallFont)
    : em_(em), smallFont_(smallFont), currentType_({100, 100, 100, 255}) {}

bool Editor::update(float dt) {
  // Color/Type picker
  if (this->em_.isKeyPressed(SDLK_g)) {
    this->currentType_ = green_;
  }
  if (this->em_.isKeyPressed(SDLK_r)) {
    this->currentType_ = red_;
  }
  if (this->em_.isKeyPressed(SDLK_w)) {
    this->currentType_ = gray_;
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
    this->wallsViewer_.push_back({x, y, w, h});

    // Set walls for screen resizing - Includes the type
    this->walls_.push_back(
        std::make_pair(this->currentType_,
                       NormalizedRect{(float)x / this->em_.windowWidth(),
                                      (float)y / this->em_.windowHeight(),
                                      (float)w / this->em_.windowWidth(),
                                      (float)h / this->em_.windowHeight()}));

    this->isDragging_ = false;
  }

  // Left click for delete
  if (this->em_.isMousePressed(SDL_BUTTON_RIGHT)) {
    float mx = (float)this->em_.mouseX() / this->em_.windowWidth();
    float my = (float)this->em_.mouseY() / this->em_.windowHeight();

    for (auto it = this->walls_.begin(); it != this->walls_.end(); ++it) {
      NormalizedRect r = (*it).second;
      if (mx >= r.x && mx <= r.x + r.w && my >= r.y && my <= r.y + r.h) {
        this->walls_.erase(it);
        break; // We break bc the iterator is invalid and we already deleted
      }
    }
  }

  // False = Exit
  // True = Continue
  if (this->em_.isKeyPressed(SDLK_ESCAPE)) {
    return false;
  }
  return true;
}

void Editor::render(SDL_Renderer* renderer) {
  // Setup Type Viewer
  SDL_Rect typeViewer{this->em_.windowWidth() - 50, 5, 45, 45};
  boxRGBA(renderer, typeViewer.x, typeViewer.y, typeViewer.x + typeViewer.w,
          typeViewer.y + typeViewer.h, this->currentType_.r,
          this->currentType_.g, this->currentType_.b, this->currentType_.a);

  // Draw while dragging
  if (this->isDragging_) {
    int x = std::min(dragStart_.x, this->em_.mouseX());
    int y = std::min(dragStart_.y, this->em_.mouseY());
    int w = std::abs(this->em_.mouseX() - dragStart_.x);
    int h = std::abs(this->em_.mouseY() - dragStart_.y);

    boxRGBA(renderer, x, y, x + w, y + h, this->currentType_.r,
            this->currentType_.g, this->currentType_.b,
            100); // Semi-transparent for preview
  }

  // Render walls after drawn (Scale-Work)
  for (const auto& wall : this->walls_) {
    boxRGBA(renderer, wall.second.x * this->em_.windowWidth(),
            wall.second.y * this->em_.windowHeight(),
            (wall.second.w + wall.second.x) * this->em_.windowWidth(),
            (wall.second.h + wall.second.y) * this->em_.windowHeight(),
            wall.first.r, wall.first.g, wall.first.b, 255);
  }
}
