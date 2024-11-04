// Grid.cpp

#include "Grid.h"

Grid::Grid(RenderWindow &p_window, Matrix &matrix) : window(p_window), matrix(matrix) {
    twoDimensional = matrix.isTwoDimensional();

    // get screen size
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);

    gridPosition = Vec2D(w / 2, h / 2);

    // set the last 5 mouse positions to 0, 0
    for (int i = 0; i < 5; i++) {
        lastMousePos.push_back(Vec2D(0, 0));
    }
}

void Grid::update() {


    // Check if the right mouse button is released
    if (is_mouse_button_released(SDL_BUTTON_RIGHT)) {
        lastMousePos = std::vector<Vec2D>(5);
        for (int i = 0; i < 5; i++) {
            lastMousePos.push_back(Vec2D(0, 0));
        }
        drawNumbers = true;
        gridMoving = false;
    }
    // Check if the right mouse button is pressed
    if (is_mouse_button_pressed(SDL_BUTTON_RIGHT)) {
        int x, y;
        get_mouse_position(x, y);
        if (lastMousePos[0].x == 0 && lastMousePos[0].y == 0) {
            lastMousePos[0] = Vec2D(x, y);
        }

        drawNumbers = false;
        gridMoving = true;
        gridPosition += Vec2D(x - lastMousePos[0].x, y - lastMousePos[0].y);
        lastMousePos[4] = lastMousePos[3];
        lastMousePos[3] = lastMousePos[2];
        lastMousePos[2] = lastMousePos[1];
        lastMousePos[1] = lastMousePos[0];
        lastMousePos[0] = Vec2D(x, y);
        // if all the last 5 mouse positions are the same, then the mouse is not moving
        if (lastMousePos[0].x == lastMousePos[1].x && lastMousePos[0].y == lastMousePos[1].y &&
            lastMousePos[0].x == lastMousePos[2].x && lastMousePos[0].y == lastMousePos[2].y &&
            lastMousePos[0].x == lastMousePos[3].x && lastMousePos[0].y == lastMousePos[3].y &&
            lastMousePos[0].x == lastMousePos[4].x && lastMousePos[0].y == lastMousePos[4].y) {
            drawNumbers = true;
            gridMoving = false;
        }
    }

    // Check if the left mouse button is currently pressed
    if (is_mouse_button_pressed(SDL_BUTTON_LEFT)) {
        leftButtonPressed = true;  // Set flag when the left button is pressed
    }

    // Check single and double click
    if (clickedOnce) {
        doubleClickDelay -= 1;
        if (leftButtonPressed && is_mouse_button_released(SDL_BUTTON_LEFT) && doubleClickDelay > 0) {
            doubleClick = true;
            clickedOnce = false;
            leftButtonPressed = false;
        } else if (doubleClickDelay <= 0) {
            singleClick = true;
            clickedOnce = false;
        }
    } else if (leftButtonPressed && is_mouse_button_released(SDL_BUTTON_LEFT)) {
        doubleClickDelay = 25;
        clickedOnce = true;
        leftButtonPressed = false;
    }

    if (singleClick)
        std::cout << "Single click detected\n";
    if (doubleClick)
        std::cout << "Double click detected\n";

    singleClick = false;
    doubleClick = false;
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

    if (drawNumbers) {

        // Helper function to draw the text on screen
        auto drawTextAtPosition = [&](int value, int x, int y) {
            window.drawText(std::to_string(value).c_str(), x + 5, y + 5, 10, false, gridColor);
        };

        // Draw numbers along the X-axis
        if (gridPosition.y > 0 && gridPosition.y < h) {
            int cells = (w - gridPosition.x) / scale;
            int cellsInScreen = w / scale;

            for (int i = cells - cellsInScreen; i < cells; i++) {
                drawTextAtPosition(i, gridPosition.x + i * scale, gridPosition.y);
            }
        }

        // Draw numbers along the Y-axis
        if (gridPosition.x > 0 && gridPosition.x < w) {
            int cells = (h - gridPosition.y) / scale;
            int cellsInScreen = h / scale;

            for (int i = cells - cellsInScreen; i < cells; i++) {
                drawTextAtPosition(-i, gridPosition.x, gridPosition.y + i * scale);
            }
        }
    }

    if (gridMoving) {

// Draw arrow pointing to the origin if (0, 0) is not on screen
        if (gridPosition.x > w || gridPosition.x < 0 || gridPosition.y > h || gridPosition.y < 0) {
            // Calculate the direction towards the origin
            float arrowX = (gridPosition.x < 0) ? 0 : (gridPosition.x > w) ? w : gridPosition.x;
            float arrowY = (gridPosition.y < 0) ? 0 : (gridPosition.y > h) ? h : gridPosition.y;

            // Draw an arrow at the edge of the screen pointing toward the origin
            auto drawArrow = [&](float x, float y, float dx, float dy) {

//            window.drawLine(x, y, x + dx, y + dy, 4, gridColor);
//            window.drawLine(x + dx, y + dy, x + dx - 5, y + dy - 5, 4, gridColor);
//            window.drawLine(x + dx, y + dy, x + dx + 5, y + dy - 5, 4, gridColor);

                window.drawText("(0, 0)", x + dx, y + dy, 15, true, gridColor);
            };

            // Calculate the direction of the arrow
            float dx = 0, dy = 0;
            if (gridPosition.x < 0) dx = 10;  // Arrow pointing right
            if (gridPosition.x > w) dx = -45; // Arrow pointing left
            if (gridPosition.y < 0) dy = 10;  // Arrow pointing down
            if (gridPosition.y > h) dy = -35; // Arrow pointing up

            // Draw the arrow at the calculated position
            drawArrow(arrowX, arrowY, dx, dy);
        }
    }

}




