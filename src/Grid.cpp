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

    matrix.addVector(Vec2D(3, 2));
    matrix.addVector(Vec2D(1, 1));
    matrix.addVector(Vec2D(2, 3));

}

void Grid::receiveDataProxy() {
    std::vector<Vec2D> deletedVectors = dataProxy.getDeleteVectors();
    if (deletedVectors.size() > 0) {
        std::cout << deletedVectors.size() << " vectors to be deleted\n";
        matrix.removeVectors(deletedVectors);
        std::cout << "Vectors deleted, now clearing the delete vectors\n";
        dataProxy.clearAll();
        selectedVectors.clear();
    }

}
void Grid::updateCursor() {
    if (t_VectorHoverFound) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
    }else if (t_movingVector) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
    } else {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    }
}
void Grid::handleMouseInputs() {
    t_leftButtonPressed = is_mouse_button_pressed(SDL_BUTTON_LEFT);
    t_middleButtonPressed = is_mouse_button_pressed(SDL_BUTTON_MIDDLE);
    t_rightButtonPressed = is_mouse_button_pressed(SDL_BUTTON_RIGHT);

    t_leftButtonWasReleased = was_mouse_button_released(SDL_BUTTON_LEFT); dataProxy.leftButtonReleased = t_leftButtonWasReleased;
    t_middleButtonWasReleased = was_mouse_button_released(SDL_BUTTON_MIDDLE);
    t_rightButtonWasReleased = was_mouse_button_released(SDL_BUTTON_RIGHT);
}

void Grid::manageDragging() {
    // Check if mouse is within the grid area
    if (GridRect.contains(t_mouseX, t_mouseY)) {
        // Handle right mouse button dragging
        if (t_rightButtonPressed) {
            if (!t_isDraggingRight) {  // Start dragging
                t_initialRightClickPos = Vec2D(t_mouseX, t_mouseY);
                t_isDraggingRight = true;
            } else {  // Update dragging state only if the mouse has moved
                int deltaX = t_mouseX - t_initialRightClickPos.x;
                int deltaY = t_mouseY - t_initialRightClickPos.y;

                // Only consider as dragging if there is movement
                if (deltaX != 0 || deltaY != 0) {
                    // Perform actions based on the dragging distance (deltaX, deltaY)
                    // Example: move an object based on deltaX and deltaY
                    // In this case, move the grid position based on the dragging distance
                    gridPosition += Vec2D(deltaX, deltaY);
                    // reset the initial click position to the current mouse position
                    t_initialRightClickPos = Vec2D(t_mouseX, t_mouseY);
                }
            }
        } else {
            t_isDraggingRight = false;  // Stop dragging when the button is released
        }

        // Handle left mouse button dragging
        if (t_leftButtonPressed) {
            if (!t_isDraggingLeft) {  // Start dragging
                t_initialLeftClickPos = Vec2D(t_mouseX, t_mouseY);
                t_isDraggingLeft = true;
            } else {  // Update dragging state only if the mouse has moved
                int deltaX = t_mouseX - t_initialLeftClickPos.x;
                int deltaY = t_mouseY - t_initialLeftClickPos.y;

                // Only consider as dragging if there is movement
                if (deltaX != 0 || deltaY != 0) {
                    // Perform actions based on the dragging distance (deltaX, deltaY)
                    // Example: move an object based on deltaX and deltaY
                }
            }
        } else {
            t_isDraggingLeft = false;  // Stop dragging when the button is released
        }
    }
}

void Grid::handleVectorInteractions() {

    // Check if Mouse is Hovering a vector
    //-----------------------------------
    t_VectorHoverFound = false;
    Vec2D hoveredVector;

    if (GridRect.contains(t_mouseX, t_mouseY)) {

        // Get the grid position of the mouse
        float gridX = (t_mouseX - gridPosition.x) / scale;
        float gridY = (gridPosition.y - t_mouseY) / scale;

        // Check if the mouse is hovering over a vector
        std::vector<Vec2D> vectors = matrix.getVectors();
        for (auto &vec : vectors) {
            if (vec.x - gridX < 0.1 && vec.y - gridY < 0.1 && vec.x - gridX > -0.1 && vec.y - gridY > -0.1) {
                t_VectorHoverFound = true;
                hoveredVector = vec;
                break;
            }
        }

        // Connect Vectors
        //----------------
        if (dataProxy.connectVectors) {
            t_toConnectVectors = selectedVectors;
            if (t_leftButtonWasReleased) {
                if (!is_key_pressed(SDLK_LSHIFT) && t_VectorHoverFound) {
                    // connect all the vectors to the hovered vector
                    for (int i = 0; i < t_toConnectVectors.size(); i++) {
                        matrix.addConnectedVector(t_toConnectVectors[i], hoveredVector);
                    }
                    selectedVectors.clear();
                    selectedVectors = {hoveredVector};
                }
            }

        }

        // Check for selection and deselection of vectors
        //----------------------------------------------
        if (t_leftButtonWasReleased) {
            if (!is_key_pressed(SDLK_LSHIFT)) {
                selectedVectors.clear();
            }

            if (t_VectorHoverFound) {

                if (isVectorSelected(hoveredVector)) {
                    removeVectorSelection(hoveredVector);
                } else {
                    selectedVectors.push_back(hoveredVector);
                }
            }
        }



        // Moving Vectors
        //---------------
        // check if it clicked 'G'
        if (!t_movingVector && selectedVectors.size() > 0 && was_key_released(SDLK_g)) {
            t_movingVector = true;
            t_vectorsToMove = selectedVectors;
            t_connectedVectorsToMove.clear();
            t_movingConnections.clear();
            // for all the vectors to move, check all the connected vectors
            std::vector<std::vector<Vec2D>> connectedVectors = matrix.getConnectedVectors();
            for (int i = 0; i < t_vectorsToMove.size(); i++) {
                std::vector<Vec2D> connectedVectorsToMove;
                for (int j = 0; j < connectedVectors.size(); j++) {
                    if (connectedVectors[j][0] == t_vectorsToMove[i]) {
                        connectedVectorsToMove.push_back(connectedVectors[j][1]);
                    }
                    if (connectedVectors[j][1] == t_vectorsToMove[i]) {
                        connectedVectorsToMove.push_back(connectedVectors[j][0]);
                    }
                }
                t_connectedVectorsToMove.push_back(connectedVectorsToMove);
            }
            // check if the vectors to move are connected to each other, store them in a separate vector
            for (int i = 0; i < t_vectorsToMove.size(); i++) {
                for (int j = 0; j < t_vectorsToMove.size(); j++) {
                    if (i != j) {
                        for (int k = 0; k < t_connectedVectorsToMove[i].size(); k++) {
                            if (t_connectedVectorsToMove[i][k] == t_vectorsToMove[j]) {
                                t_movingConnections.push_back({t_vectorsToMove[i], t_vectorsToMove[j]});
                                t_connectedVectorsToMove[i].erase(t_connectedVectorsToMove[i].begin() + k);
                            }
                        }
                    }
                }
            }
            // remove the connection between the vectors to move
            for (int i = 0; i < t_vectorsToMove.size(); i++) {
                matrix.removeConnectedVector(t_vectorsToMove[i]);
            }
            t_initialToMoveVectorsPos = selectedVectors;
            matrix.removeVectors(selectedVectors);
            selectedVectors.clear();
            t_lastMousePos = Vec2D(t_mouseX, t_mouseY);
        }
        if (t_movingVector) {
            // get velocity of the mouse according to the grid
            float velocityX = (t_mouseX - t_lastMousePos.x) / scale;
            float velocityY = (t_lastMousePos.y - t_mouseY) / scale;


            // move the vectors
            for (int i = 0; i < t_vectorsToMove.size(); i++) {
                t_vectorsToMove[i] += Vec2D(velocityX, velocityY);
            }

            // move the connections
            for (int i = 0; i < t_movingConnections.size(); i++) {
                t_movingConnections[i][0] += Vec2D(velocityX, velocityY);
                t_movingConnections[i][1] += Vec2D(velocityX, velocityY);
            }


            t_lastMousePos = Vec2D(t_mouseX, t_mouseY);
        }

        if (t_movingVector && t_leftButtonWasReleased) {
            // Place the selected vectors in their positions
            for (int i = 0; i < t_vectorsToMove.size(); i++) {
                // Connect vectors, and connect moving vectors that are supposed to be connected
                for (int j = 0; j < t_connectedVectorsToMove[i].size(); j++) {
                    matrix.addConnectedVector(t_vectorsToMove[i], t_connectedVectorsToMove[i][j]);
                }
                for (int j = 0; j < t_movingConnections.size(); j++) {
                    matrix.addConnectedVector(t_movingConnections[j][0], t_movingConnections[j][1]);
                }
                matrix.addVector(t_vectorsToMove[i]);
            }

            t_movingVector = false;
        }

        if (t_movingVector && t_rightButtonWasReleased) {
            // Place the selected vectors in their initial position
            t_movingVector = false;
        }



        // Add a vector by pressing 'V'
        if (was_key_released(SDLK_v)) {
            matrix.addVector(Vec2D(gridX, gridY));
        }

    }
}



void Grid::update() {
    // adjust the grid position based on the window size
   GridRect = Rect(0, 0, window.getWidth() - dataProxy.panelWidth, window.getHeight());

   get_mouse_position(t_mouseX, t_mouseY);

   receiveDataProxy();

   handleMouseInputs();

   if (t_leftButtonWasReleased) {
       std::cout << "Left button was released\n";
   }
   if (was_mouse_button_released(SDL_BUTTON_LEFT)) {
       std::cout << "Left button was released\n";
   }

   manageDragging();

   handleVectorInteractions();

    updateCursor();

    // For sending dataProxy
    dataProxy.setSelectedVectors(selectedVectors);

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
    // Draw the moving vectors
    if (t_movingVector) {
        for (auto &vec : t_vectorsToMove) {
            Vec2D pos;
            pos.x = gridPosition.x + vec.x * scale;
            pos.y = gridPosition.y - vec.y * scale;
            window.fillCircle(pos.x, pos.y, 5, Color::Green());
        }
    }
    // Draw lines between the vectors to move and movingConnectedVectors
    if (t_movingVector) {
        for (int i = 0; i < t_vectorsToMove.size(); i++) {
            Vec2D pos1;
            pos1.x = gridPosition.x + t_vectorsToMove[i].x * scale;
            pos1.y = gridPosition.y - t_vectorsToMove[i].y * scale;
            for (int j = 0; j < t_connectedVectorsToMove[i].size(); j++) {
                Vec2D pos2;
                pos2.x = gridPosition.x + t_connectedVectorsToMove[i][j].x * scale;
                pos2.y = gridPosition.y - t_connectedVectorsToMove[i][j].y * scale;
                window.drawLine(pos1.x, pos1.y, pos2.x, pos2.y, 2, Color::Green());
            }
        }
    }
    // Draw lines between moving connections
    if (t_movingVector) {
        for (auto &connection : t_movingConnections) {
            Vec2D pos1;
            pos1.x = gridPosition.x + connection[0].x * scale;
            pos1.y = gridPosition.y - connection[0].y * scale;
            Vec2D pos2;
            pos2.x = gridPosition.x + connection[1].x * scale;
            pos2.y = gridPosition.y - connection[1].y * scale;
            window.drawLine(pos1.x, pos1.y, pos2.x, pos2.y, 2, Color::Blue());
        }
    }



    // if the connectVectors is true, then draw the lines between selected vectors and the mouse
    if (dataProxy.connectVectors) {
        for (auto &connectVec : t_toConnectVectors) {
            Vec2D pos;
            pos.x = gridPosition.x + connectVec.x * scale;
            pos.y = gridPosition.y - connectVec.y * scale;
            window.drawLine(pos.x, pos.y, t_mouseX, t_mouseY, 2, Color::Orange());
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




