// Grid.h

#ifndef MATH_GRID_H
#define MATH_GRID_H

#include <iostream>
#include <SDL.h>

#include "RenderWindow.h"
#include "Color.h"
#include "Vec2D.h"
#include "Matrix.h"
#include "MouseHandler.h"

class Grid {
private:

    RenderWindow& window;


    Matrix& matrix;

    Color gridColor = Color::LightBlue();

    bool twoDimensional;

    float scale = 50;

    Vec2D gridPosition = Vec2D(0, 0);
    Vec2D lastMousePos = Vec2D(0, 0);

public:
    Grid(RenderWindow& p_window, Matrix& matrix);
    void update();
    void drawGrid();

    void setScale(float p_scale) { scale = p_scale; }
    float getScale() { return scale; }

    void setGridColor(Color p_color) { gridColor = p_color; }
};

#endif //MATH_GRID_H
