#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

    return 0;
}
