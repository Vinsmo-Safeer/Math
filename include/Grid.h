// Grid.h

#ifndef MATH_GRID_H
#define MATH_GRID_H

#include <iostream>
#include <SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <memory> // For smart pointers

#include "RenderWindow.h"
#include "Color.h"
#include "Vec2D.h"
#include "Matrix.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "PopUpMenu.h"

class Grid {
private:

    RenderWindow& window;

    Matrix& matrix;

    std::unique_ptr<PopUpMenu> popUpMenu; // Pointer to manage the popup menu dynamically


    Color gridColor = Color::LightBlue();

    bool twoDimensional;

    float scale = 50;

    Vec2D gridPosition = Vec2D(0, 0);
    std::vector<Vec2D> lastMousePos = std::vector<Vec2D>(5);

    bool drawNumbers = false;

    bool gridMoving = false;

    bool leftButtonPressed = false;

    bool isRightDrag = false;

    // for single click and double click detection
    bool singleClick = false;
    bool doubleClick = false;
    int doubleClickDelay = 0;
    bool clickedOnce = false;

    // for pop up menu
    bool rightClickedOnce = false;

    std::vector<Vec2D> selectedVectors;

public:
    Grid(RenderWindow& p_window, Matrix& matrix);
    void update();
    void drawGrid();

    void setScale(float p_scale) { scale = p_scale; }
    float getScale() { return scale; }

    void setGridColor(Color p_color) { gridColor = p_color; }
    void createPopUpWindow();

    void reset();
};

#endif //MATH_GRID_H
