#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>

class Player {
private:
    int radius_;
    int x_, y_;
public:
    Player(int r);

    void updatePosition(int mousex_, int mousey_);
    void render(SDL_Renderer* renderer);

    int x() const { return x_; }
    int y() const { return y_; }
};
