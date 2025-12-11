#pragma once
#include <SDL2/SDL.h>

class Enemy {
private:
    SDL_Rect rect_;
    int vx_, vy_; // Velocity
    float fx_, fy_;
public:

    Enemy(int x, int y, int w, int h, int velX, int velY);
    void update(float dt, int windowWidth, int windowHeight);
    void render(SDL_Renderer* renderer);

    SDL_Rect rect() const { return rect_; } // If FPS bad, maybe turn this into reference
};
