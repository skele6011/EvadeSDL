#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Core/Window.hpp"
#include "Core/Initializer.hpp"
#include "Core/EventManager.hpp"
#include "Core/Texture.hpp"

#include "Utils/Collision.hpp"
#include "Utils/Enemy.hpp"
#include "Utils/Player.hpp"

#include "Levels/Practice.cpp"

int main() {
    Practice practice;
    return practice.startGame();
}
