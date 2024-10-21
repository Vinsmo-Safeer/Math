// Grid.cpp

#include "Grid.h"

Grid::Grid(RenderWindow &p_window, Matrix &matrix) : window(p_window), matrix(matrix) {
    twoDimensional = matrix.isTwoDimensional();

    // get screen size
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);

    gridPosition = Vec2D(w / 2, h / 2);
}

void Grid::update() {
    if (is_mouse_button_released(SDL_BUTTON_RIGHT)) {
        lastMousePos = Vec2D(0, 0);
    }
    if (is_mouse_button_pressed(SDL_BUTTON_RIGHT)) {
        int x, y;
        get_mouse_position(x, y);
        if (lastMousePos.x == 0 && lastMousePos.y == 0) {
            lastMousePos = Vec2D(x, y);
        }
        gridPosition += Vec2D(x - lastMousePos.x, y - lastMousePos.y);
        lastMousePos = Vec2D(x, y);
    }

}

void Grid::drawGrid() {
    // get screen size
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);


    // draw radius 3 circle at origin
    SDL_SetRenderDrawColor(window.getRenderer(), gridColor.r, gridColor.g, gridColor.b, gridColor.a);
    window.fillCircle(gridPosition.x, gridPosition.y, 3, gridColor);

    // draw x-axis
    if (gridPosition.y > 0 && gridPosition.y < h) {
        window.fillRect(0, gridPosition.y, w, 3, gridColor);
    }
    // draw y-axis
    if (gridPosition.x > 0 && gridPosition.x < w) {
        window.fillRect(gridPosition.x, 0, 3, h, gridColor);
    }

    // draw grid lines based on grid position
    for (int i = gridPosition.x; i < w; i += scale) {
        window.fillRect(i, 0, 1, h, gridColor);
    }
    for (int i = gridPosition.x; i > 0; i -= scale) {
        window.fillRect(i, 0, 1, h, gridColor);
    }
    for (int i = gridPosition.y; i < h; i += scale) {
        window.fillRect(0, i, w, 1, gridColor);
    }
    for (int i = gridPosition.y; i > 0; i -= scale) {
        window.fillRect(0, i, w, 1, gridColor);
    }


}




