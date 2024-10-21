// RenderWindow.h

#ifndef MATH_RENDERWINDOW_H
#define MATH_RENDERWINDOW_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Color.h"

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Color defaultColor = Color::White();


public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    float getRefreshRate();
    void cleanUp();
    void clear();

    void drawLine(float x1, float y1, float x2, float y2, Color color);
    void drawLine(float x1, float y1, float x2, float y2, int thickness, Color color);
    void drawRect(float x, float y, float w, float h, Color color);
    void drawRect(float x, float y, float w, float h, int thickness, Color color);
    void fillRect(float x, float y, float w, float h, Color color);
    void drawCircle(float x, float y, float r, Color color);
    void drawCircle(float x, float y, float r, int thickness, Color color);
    void fillCircle(float x, float y, float r, Color color);

    void display();


    SDL_Window* getWindow() { return window; }
    SDL_Renderer* getRenderer() { return renderer; }
};


#endif //MATH_RENDERWINDOW_H
