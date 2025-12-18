#include "Stage.hpp"
#include <SDL2/SDL.h>

// --- Constructor ---
Stage::Stage(Window& window, EventManager& events, int width, int height)
    : window_(window), events_(events), windowWidth_(width), windowHeight_(height)
{
    // Nothing else to initialize
}
// --- end: Constructor ---


// --- Run ---
// Shared main loop for all levels
int Stage::run() {
    onEnter();
    this->lastTime_ = SDL_GetTicks();
    bool running = true;

    while (running) {
        Uint32 frameStart = SDL_GetTicks();

        // --- Event stuff ---
        running = this->events_.pollEvents();
        this->windowHeight_ = this->events_.windowHeight(); this->windowWidth_ = this->events_.windowWidth();
        handleEvents();
        // --- end: Event stuff ---

        Uint32 now = SDL_GetTicks();
        this->deltaTime_ = (now - this->lastTime_) / 1000.0f;
        this->lastTime_ = now;

        update(this->deltaTime_);
        this->window_.beginFrame();
        render();
        this->window_.endFrame();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime);
    }

    onExit();
    return 0;
}
// --- end: Run ---

