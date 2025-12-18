#pragma once
#include <SDL2/SDL.h>
#include "../SDLLibrary/SDLLibrary.h"

class Stage {
protected:
    Window& window_;
    EventManager& events_;
    int windowWidth_;
    int windowHeight_;
    const Uint32 TARGET_FPS = 360;
    const Uint32 FRAME_DELAY = 1000 / TARGET_FPS;
    Uint32 lastTime_ = 0;
    float deltaTime_ = 0.0f;

public:
    Stage(Window& window, EventManager& events, int width, int height);

    // --- Main loop ---
    int run();

protected:
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void handleEvents() {}
    virtual void update(float /*dt*/) {}
    virtual void render() {}
};
