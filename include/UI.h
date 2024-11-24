#ifndef MATH_UI_H
#define MATH_UI_H

#include <iostream>
#include "RenderWindow.h"
#include "MouseHandler.h"

class UI {
public:

    UI(RenderWindow& window, int x, int y, int width, int height) : window(window), x(x), y(y), width(width), height(height) {}

    void show() {
        std::cout << "Showing UI" << std::endl;
    }

    void hide() {
        std::cout << "Hiding UI" << std::endl;
    }

    void update();
    void render();

private:

    int x, y;
    int width, height;

    std::string command;

    RenderWindow& window;
};

#endif //MATH_UI_H
