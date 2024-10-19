#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"

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

    bool running = true;

    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        window.clear();

        // Draw defaultAlpha line
        window.drawLine(0, 0, 200, 200,5 , Color::Red());
        window.drawRect(100, 100, 200, 200, 5, Color::Green());


        window.display();

    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}
