// Grid.cpp

#include <iomanip>
#include "Grid.h"

Grid::Grid(RenderWindow &p_window, Matrix &matrix) : window(p_window), matrix(matrix), popUpMenu(nullptr) {
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

//    std::cout << "Is Right Drag: " << isRightDrag << std::endl;

    // Check if the right mouse button is released
    if (is_mouse_button_released(SDL_BUTTON_RIGHT)) {
        lastMousePos = std::vector<Vec2D>(5);
        for (int i = 0; i < 5; i++) {
            lastMousePos.push_back(Vec2D(0, 0));
        }
        drawNumbers = true;
        gridMoving = false;

        // mouse clickedAndReleased
        if (rightClickedOnce) {

            if (isRightDrag) {
                isRightDrag = false;
            } else {

                // Create A popup menu

                /////////////////////////////////////////////
                ///////STILL IN PROGRESS/////////////////////
                /////////////////////////////////////////////

//                std::cout << "Creating a popup menu\n";
//                int x, y;
//                get_mouse_position(x, y);
//                // Create and show the popup menu dynamically
//                popUpMenu = std::make_unique<PopUpMenu>(x, y, "rightClick");
//                popUpMenu->show(x, y);

            }
            rightClickedOnce = false;
        }


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
        if (x != lastMousePos[0].x || y != lastMousePos[0].y) {
            gridPosition += Vec2D(x - lastMousePos[0].x, y - lastMousePos[0].y);
            isRightDrag = true;
        }
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


        // for pop up menu
        rightClickedOnce = true;
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

    /////////////////////////////////////////////
    ///////STILL IN PROGRESS/////////////////////
    /////////////////////////////////////////////

//    // zoom in and out
//    if (is_scroll_up()) {
//        scale += 10;
//        reset_scroll();
//        std::cout << "scale: " << scale << std::endl;
//    }
//    if (is_scroll_down()) {
//        scale -= 10;
//        reset_scroll();
//        std::cout << "scale: " << scale << std::endl;
//    }

    // check if pressed middle mouse button
    if (is_mouse_button_pressed(SDL_BUTTON_MIDDLE)) {
        // get mouse position
        int x, y;
        get_mouse_position(x, y);
        // get where the mouse is on the grid
        float gridX = (x - gridPosition.x) / scale;
        float gridY = (gridPosition.y - y) / scale;
//        std::cout << "Grid position: (" << gridX << ", " << gridY << ")\n";
        // set to a vector
        Vec2D gridPos = Vec2D(gridX, gridY);
        // add to the matrix
        matrix.addVector(gridPos);

        if (is_key_pressed(SDL_SCANCODE_LALT)) {
        }
    }


    if (is_mouse_button_pressed(SDL_BUTTON_RIGHT)) {

        // unless shift is pressed, clear the selected vectors
        if (!is_key_pressed(SDLK_LSHIFT)) {
            selectedVectors.clear();
            std::cout << "Selected vectors cleared\n";
        }

        // if there is a vector close to the mouse position, add that vector to the selected vectors
        int x, y;
        get_mouse_position(x, y);
        // get where the mouse is on the grid
        float gridX = (x - gridPosition.x) / scale;
        float gridY = (gridPosition.y - y) / scale;
        std::vector<Vec2D> vectors = matrix.getVectors();
        for (auto &vec : vectors) {
            if (vec.x - gridX < 0.1 && vec.y - gridY < 0.1 && vec.x - gridX > -0.1 && vec.y - gridY > -0.1) {
                selectedVectors.push_back(vec);
            }
        }



    }


    reset();
}

void Grid::reset() {
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

    // draw grid lines based on grid position and scale
    int cellSizeMultiplier = std::max(1, static_cast<int>(scale / 50)); // Ensure cellSizeMultiplier is at least 1
    int minCellSize = 30; // Minimum size of each cell in pixels

    int cellSize = std::max(static_cast<int>(scale / cellSizeMultiplier), minCellSize);
//    std::cout << "cellSizeMultiplier: " << cellSizeMultiplier << ", cellSize: " << cellSize << std::endl;

// Draw vertical grid lines
    for (int i = gridPosition.x; i < w; i += cellSize) {
        window.fillRect(i, 0, 1, h, gridColor);
    }
    for (int i = gridPosition.x; i > 0; i -= cellSize) {
        window.fillRect(i, 0, 1, h, gridColor);
    }

// Draw horizontal grid lines
    for (int i = gridPosition.y; i < h; i += cellSize) {
        window.fillRect(0, i, w, 1, gridColor);
    }
    for (int i = gridPosition.y; i > 0; i -= cellSize) {
        window.fillRect(0, i, w, 1, gridColor);
    }

    if (drawNumbers) {
        // Helper function to draw text on screen with formatted value
        auto drawTextAtPosition = [&](float value, int x, int y) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(value == static_cast<int>(value) ? 0 : 1) << value;
            window.drawText(oss.str().c_str(), x + 5, y + 5, 10, false, gridColor);
        };

        int cellSize = std::max(static_cast<int>(scale / cellSizeMultiplier), 30);

        // Draw numbers along the X-axis
        if (gridPosition.y > 0 && gridPosition.y < h) {
            int cells = (w - gridPosition.x) / cellSize;
            int cellsInScreen = w / cellSize;

            for (float i = cells - cellsInScreen; i < cells; i += 1.0f / cellSizeMultiplier) {
                int posX = gridPosition.x + static_cast<int>(i * cellSize);
                if (posX >= 0 && posX <= w) {
                    drawTextAtPosition(i, posX, gridPosition.y);
                }
            }
        }

        // Draw numbers along the Y-axis
        if (gridPosition.x > 0 && gridPosition.x < w) {
            int cells = (h - gridPosition.y) / cellSize;
            int cellsInScreen = h / cellSize;

            for (float i = cells - cellsInScreen; i < cells; i += 1.0f / cellSizeMultiplier) {
                int posY = gridPosition.y + static_cast<int>(i * cellSize);
                if (posY >= 0 && posY <= h) {
                    drawTextAtPosition(-i, gridPosition.x, posY);
                }
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

    // Draw the matrix vectors
    for (auto &vec : matrix.getVectors()) {
//        Vec2D pos = gridPosition + vec * scale;
        Vec2D pos;
        pos.x = gridPosition.x + vec.x * scale;
        pos.y = gridPosition.y - vec.y * scale;
//        std::cout << "pos.y: " << pos.y << " = " << gridPosition.y << " + " << vec.y << " * " << scale << std::endl;

        // check if it is in the selected vectors, then change the color to orange
        bool isSelected = false;
        for (auto &selectedVec : selectedVectors) {
            if (selectedVec == vec) {
                isSelected = true;
                break;
            }
        }
        if (isSelected) {
            window.fillCircle(pos.x, pos.y, 3, Color::Orange());
        } else {
            window.fillCircle(pos.x, pos.y, 3, Color::Black());
        }
    }

}




