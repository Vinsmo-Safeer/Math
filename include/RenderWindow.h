// RenderWindow.h

#ifndef MATH_RENDERWINDOW_H
#define MATH_RENDERWINDOW_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

#include "Color.h"
#include "FontUtils.h"

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Color defaultColor = Color::White();

    std::map<int, TTF_Font*> fontCache;

    TTF_Font* getFont(int size) {
        if (fontCache.find(size) == fontCache.end()) {
            TTF_Font* newFont = TTF_OpenFont("../assets/fonts/arial.ttf", size);
            if (newFont == nullptr) {
                std::cout << "Failed to load font. Error: " << TTF_GetError() << std::endl;
                return nullptr;
            }
            fontCache[size] = newFont;
        }
        return fontCache[size];
    }

public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    ~RenderWindow();
    float getRefreshRate();
    void cleanUp();
    void clear();

    int getWidth();
    int getHeight();

    void drawLine(float x1, float y1, float x2, float y2, Color color);
    void drawLine(float x1, float y1, float x2, float y2, int thickness, Color color);
    void drawRect(float x, float y, float w, float h, Color color);
    void drawRect(float x, float y, float w, float h, int thickness, Color color);
    void fillRect(float x, float y, float w, float h, Color color);
    void drawCircle(float x, float y, float r, Color color);
    void drawCircle(float x, float y, float r, int thickness, Color color);
    void fillCircle(float x, float y, float r, Color color);

    void drawText(const char* text, int x, int y, int size, bool bold, Color color);

    void display();

    int measureTextWidth(const char* text, int fontSize);


    SDL_Window* getWindow() { return window; }
    SDL_Renderer* getRenderer() { return renderer; }
};


#endif //MATH_RENDERWINDOW_H
