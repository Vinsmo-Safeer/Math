#include <valarray>
#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    : window(nullptr), renderer(nullptr) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    SDL_RenderClear(renderer);
}


void RenderWindow::drawLine(float x1, float y1, float x2, float y2, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void RenderWindow::drawLine(float x1, float y1, float x2, float y2, int thickness, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < thickness; i++) {
        SDL_RenderDrawLine(renderer, x1, y1 + i, x2, y2 + i);
    }
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}

void RenderWindow::drawRect(float x, float y, float w, float h, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void RenderWindow::drawRect(float x, float y, float w, float h, int thickness, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < thickness; i++) {
        SDL_Rect rect;
        rect.x = x - i;
        rect.y = y - i;
        rect.w = w + i * 2;
        rect.h = h + i * 2;
        SDL_RenderDrawRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}

void RenderWindow::fillRect(float x, float y, float w, float h, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}

void RenderWindow::drawCircle(float x, float y, float r, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 0; i < 360; i++) {
        float x1 = x + r * cos(i);
        float y1 = y + r * sin(i);
        float x2 = x + r * cos(i + 1);
        float y2 = y + r * sin(i + 1);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void RenderWindow::drawCircle(float x, float y, float r, int thickness, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < thickness; i++) {
        for (int j = 0; j < 360; j++) {
            float x1 = x + r * cos(j);
            float y1 = y + r * sin(j);
            float x2 = x + r * cos(j + 1);
            float y2 = y + r * sin(j + 1);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}

void RenderWindow::fillCircle(float x, float y, float r, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < 360; j++) {
            float x1 = x + i * cos(j);
            float y1 = y + i * sin(j);
            float x2 = x + i * cos(j + 1);
            float y2 = y + i * sin(j + 1);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}


void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}