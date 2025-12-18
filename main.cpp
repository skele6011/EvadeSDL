#include "SDLLibrary/SDLLibrary.h"
#include "Levels/PracticeLevel.hpp"
#include <iostream>

int main() {
    // --- Initialize SDL and helpers ---
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG);
    if (!sdl.sdlInitialized() || !sdl.imgInitialized()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    Window window("Practice Level", 1920, 1080);
    EventManager events(window.window(), false);

    // --- Create Practice level ---
    Practice practiceLevel(sdl, window, events);

    // --- Start the game ---
    int result = practiceLevel.startGame();

    if (result == 0) {
        std::cout << "Player quit the game." << std::endl;
    } else if (result == 1) {
        std::cout << "Game restarted (if you hooked it up to menus)." << std::endl;
    }

    return 0;
}
