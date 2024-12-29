// Grid.cpp

#include <iomanip>
#include "Grid.h"
#include "Rect.h"

Grid::Grid(RenderWindow &p_window, Matrix &p_matrix, DataProxy &p_dataProxy) : window(p_window), matrix(p_matrix), dataProxy(p_dataProxy), popUpMenu(nullptr) {
    twoDimensional = p_matrix.isTwoDimensional();

    GridRect = Rect(0, 0, window.getWidth() - dataProxy.panelWidth, window.getHeight());

    gridPosition = Vec2D(GridRect.w / 2, GridRect.h / 2);

    // set the last 5 mouse positions to 0, 0
    for (int i = 0; i < 5; i++) {
        lastMousePos.push_back(Vec2D(0, 0));
    }


//    // Create a "four arrows" system cursors
//    SDL_Cursor* fourArrowsCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
//    if (!fourArrowsCursor) {
//        std::cerr << "Failed to create system cursors! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//    }
//
//    // Set the cursors
//    SDL_SetCursor(fourArrowsCursor);

}

void Grid::update() {

   GridRect = Rect(0, 0, window.getWidth() - dataProxy.panelWidth, window.getHeight());


    // For receiving dataProxy
    std::vector<Vec2D> deletedVectors = dataProxy.getDeleteVectors();
    for (int i = 0; i < deletedVectors.size(); i++) {
        matrix.removeVector(deletedVectors[i]);
        std::cout << "Vector removed at " << deletedVectors[i].x << ", " << deletedVectors[i].y << std::endl;
    }
    dataProxy.clearAll();


    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));

    // Check if the middle mouse button is released
    if (!middleButtonPressed && is_mouse_button_released(SDL_BUTTON_MIDDLE)) {
        canCreateVector = true;
    } else if (middleButtonPressed && is_mouse_button_released(SDL_BUTTON_MIDDLE)) {
        canCreateVector = true;
    } else if (middleButtonPressed && is_mouse_button_pressed(SDL_BUTTON_MIDDLE)) {
        canCreateVector = false;
    }

//    if (is_mouse_button_pressed(SDL_BUTTON_LEFT)) { leftButtonPressed = true; } else { leftButtonPressed = false; }
    if (is_mouse_button_pressed(SDL_BUTTON_RIGHT)) { rightButtonPressed = true; } else { rightButtonPressed = false; }
    if (is_mouse_button_pressed(SDL_BUTTON_MIDDLE)) { middleButtonPressed = true; } else { middleButtonPressed = false; }
    if (is_key_pressed(SDLK_LSHIFT)) { lShiftPressed = true; } else { lShiftPressed = false; }
    if (is_key_pressed(SDLK_LALT)) { lAltPressed = true; } else { lAltPressed = false; }

    // check if the mouse hovering over a vector
    int x, y;
    get_mouse_position(x, y);
    if (GridRect.contains(x, y)) {

        // get where the mouse is on the grid
        float gridX = (x - gridPosition.x) / scale;
        float gridY = (gridPosition.y - y) / scale;
        std::vector<Vec2D> vectors = matrix.getVectors();
        for (auto &vec: vectors) {
            if (vec.x - gridX < 0.1 && vec.y - gridY < 0.1 && vec.x - gridX > -0.1 && vec.y - gridY > -0.1) {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
                if (is_mouse_button_pressed(SDL_BUTTON_LEFT)) {
                    moveVectors = true;
                    initialToMoveVectorPos = Vec2D(gridX, gridY);
                }
                break;
            }
        }
        if (is_mouse_button_released(SDL_BUTTON_LEFT)) {
            moveVectors = false;
            vectorsToMove.clear();
            initialToMoveVectorsPos.clear();
            initialToMoveVectorPos = Vec2D(0, 0);
        }


        if (moveVectors) {
            // if there is a big gap between the initial position and the current mouse position, then move the vectors, if there is not then don't move the vectors
            if (std::abs(initialToMoveVectorPos.x - gridX) > 0.1 || std::abs(initialToMoveVectorPos.y - gridY) > 0.1) {
                vectorsToMove = selectedVectors;
            } else {
                vectorsToMove.clear();
            }

            if (initialToMoveVectorsPos.size() == 0) {
                for (int i = 0; i < vectorsToMove.size(); i++) {
                    initialToMoveVectorsPos.push_back(vectorsToMove[i]);
                }
            } else {
                // get the mouse velocity from the initialToMoveVectorPos and the current mouse position
                float velocityX = gridX - initialToMoveVectorPos.x;
                float velocityY = gridY - initialToMoveVectorPos.y;
                for (int i = 0; i < vectorsToMove.size(); i++) {
                    matrix.moveVector(vectorsToMove[i], initialToMoveVectorsPos[i].x + velocityX,
                                      initialToMoveVectorsPos[i].y + velocityY);
                }
            }

        }
    }




    if (GridRect.contains(x, y)) {

        // Check if the right mouse button is released
        if (!rightButtonPressed) {
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
                }
                rightClickedOnce = false;
            }


        }


        // Check if the right mouse button is pressed
        if (rightButtonPressed) {
            if (lastMousePos[0].x == 0 && lastMousePos[0].y == 0) {
                lastMousePos[0] = Vec2D(x, y);
            }

            drawNumbers = false;
            gridMoving = true;
            if (x != lastMousePos[0].x || y != lastMousePos[0].y) {
                gridPosition += Vec2D(x - lastMousePos[0].x, y - lastMousePos[0].y);
                isRightDrag = true;
                SDL_SetCursor(openHandCursor);
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
        if (middleButtonPressed && canCreateVector) {

            int x, y;
            get_mouse_position(x, y);

            // get where the mouse is on the grid
            float gridX = (x - gridPosition.x) / scale;
            float gridY = (gridPosition.y - y) / scale;

            // set to a vector
            Vec2D gridPos = Vec2D(gridX, gridY);

            // check if there is already a vector at that position, if so check for connections
            std::vector<Vec2D> vectors = matrix.getVectors();
            for (auto &vec: vectors) {
                if (vec.x - gridPos.x < 0.1 && vec.y - gridPos.y < 0.1 && vec.x - gridPos.x > -0.1 &&
                    vec.y - gridPos.y > -0.1) {
                    if (lAltPressed) {
                        std::cout << "Alt is pressed and vector is already there\n";
                        if (selectedVectors.size() > 0) {
                            for (int i = 0; i < selectedVectors.size(); i++) {
                                matrix.addConnectedVector(selectedVectors[i], vec);
                            }
                        } else {
                            // if there is no selected vector, then connect the last vector added
                            if (toBeConnected.x != 0 && toBeConnected.y != 0) {
                                matrix.addConnectedVector(toBeConnected, vec);
                                toBeConnected = Vec2D(vec.x, vec.y);
                            } else {
                                toBeConnected = vec;
                            }
                        }
                    } else {
                        toBeConnected = Vec2D(0, 0);
                    }
                    return;
                }
            }

            // add the vector to the matrix
            matrix.addVector(gridPos);


            if (lAltPressed) {
                std::cout << "Alt is pressed\n";
                // if alt is pressed, connect the vectors which are selected
                if (selectedVectors.size() > 0) {
                    for (int i = 0; i < selectedVectors.size(); i++) {
                        matrix.addConnectedVector(selectedVectors[i], gridPos);
                    }
                } else {
                    // if there is no selected vector, then connect the last vector added
                    if (toBeConnected.x != 0 && toBeConnected.y != 0) {
                        matrix.addConnectedVector(toBeConnected, gridPos);
                        toBeConnected = Vec2D(gridPos.x, gridPos.y);
                    } else {
                        toBeConnected = gridPos;
                    }
                }


            } else {
                toBeConnected = Vec2D(0, 0);
            }

        }


        if (leftButtonPressed) {

            // unless shift is pressed, clear the selected vectors
            if (!lShiftPressed && selectedVectors.size() > 0 && !moveVectors) {
                selectedVectors.clear();
                std::cout << "Left button pressed, Left shift not pressed, moving vectors is false\n";
                std::cout << "Selected vectors cleared\n";
            }

            // if there is a vector close to the mouse position, add that vector to the selected vectors
            int x, y;
            get_mouse_position(x, y);
            // get where the mouse is on the grid
            float gridX = (x - gridPosition.x) / scale;
            float gridY = (gridPosition.y - y) / scale;
            std::vector<Vec2D> vectors = matrix.getVectors();
            for (auto &vec: vectors) {
                if (vec.x - gridX < 0.1 && vec.y - gridY < 0.1 && vec.x - gridX > -0.1 && vec.y - gridY > -0.1) {
                    selectedVectors.push_back(vec);
                }
            }
        }


        if (doubleClick) {
            int x, y;
            get_mouse_position(x, y);
            // get where the mouse is on the grid
            float gridX = (x - gridPosition.x) / scale;
            float gridY = (gridPosition.y - y) / scale;
            std::vector<Vec2D> vectors = matrix.getVectors();
            for (auto &vec: vectors) {
                if (vec.x - gridX < 0.1 && vec.y - gridY < 0.1 && vec.x - gridX > -0.1 && vec.y - gridY > -0.1) {
                    matrix.removeVector(vec);
                    std::cout << "Vector removed at " << vec.x << ", " << vec.y << std::endl;
                }
            }
        }
    }




    // For sending dataProxy
    dataProxy.addSelectedVectors(selectedVectors);

    reset();
}



void Grid::reset() {
    singleClick = false;
    doubleClick = false;
}


void Grid::drawGrid() {

    int w = GridRect.w;
    int h = GridRect.h;


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

    // Draw lines between connected vectors
    for (auto &connectedVecs : matrix.getConnectedVectors()) {
        Vec2D vec1 = connectedVecs[0];
        Vec2D vec2 = connectedVecs[1];
        Vec2D pos1;
        pos1.x = gridPosition.x + vec1.x * scale;
        pos1.y = gridPosition.y - vec1.y * scale;
        Vec2D pos2;
        pos2.x = gridPosition.x + vec2.x * scale;
        pos2.y = gridPosition.y - vec2.y * scale;
        window.drawLine(pos1.x, pos1.y, pos2.x, pos2.y, 2, Color::Black());
    }

}




