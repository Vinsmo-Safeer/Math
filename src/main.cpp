// main.cpp

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Grid.h"
#include "Utils.h"
#include "UI.h"

int FPS = 60;

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL_Init Has Failed. Error: " << SDL_GetError() << std::endl;
    } else { std::cout << "SDL_Init has succeeded!" << std::endl; }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
    } else { std::cout << "IMG_Init has succeeded!" << std::endl; }

    if (TTF_Init() == -1) {
        std::cout << "TTF_Init has failed. Error: " << SDL_GetError() << std::endl;
    } else { std::cout << "TTF_Init has succeeded!" << std::endl; }

    RenderWindow window("Math v1.0", 800, 600);

    Vec2D iHat(1, 0);
    Vec2D jHat(0, 1);
    Matrix matrix(iHat, jHat);
    Grid grid(window, matrix);

    bool showGrid = true;

    bool running = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    // FPS counter variables
    int frameCount = 0;
    float fpsTimeCounter = 0.0f;

    while (running) {

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        // Polling for events every frame
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            handleMouseInput(event);
            handleKeyInput(event);
        }

        // Fixed timestep logic
        while (accumulator >= timeStep) {
            try {
                // Update game logic here
                grid.update();

            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                running = false;
            }

            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

        window.clear();

        // Render the game
        if (showGrid) {
            grid.drawGrid();
        }

        window.display();

        // FPS calculation
        frameCount++;
        fpsTimeCounter += frameTime;

        if (fpsTimeCounter >= 1.0f) {
            FPS = frameCount;
            frameCount = 0;
            fpsTimeCounter -= 1.0f;
        }

        // Frame rate control (optional)
        float frameDuration = 1.0f / window.getRefreshRate();
        float elapsedTime = utils::hireTimeInSeconds() - currentTime;

        if (elapsedTime < frameDuration) {
            SDL_Delay((frameDuration - elapsedTime) * 1000);  // Convert to milliseconds
        }
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}
