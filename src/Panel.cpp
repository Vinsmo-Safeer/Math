#include "Panel.h"

Panel::Panel(RenderWindow& p_window, DataProxy &p_dataProxy) : window(p_window), dataProxy(p_dataProxy) {
    std::cout << "Panel created." << std::endl;
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);
    std::cout << "Window size: " << w << "x" << h << std::endl;

    setPanelWidth(w * 0.2);
}

void Panel::setPanelWidth(int width) {
    wholeWidth = width;
    panelWidth = wholeWidth - barWidth;
    dataProxy.panelWidth = wholeWidth;
    buttonHandler();
}

void Panel::reload() {
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);
    std::cout << "Window size: " << w << "x" << h << std::endl;

    setPanelWidth(w * 0.2);
}

void Panel::buttonHandler() {
    int height = window.getHeight();
    int buttonHeight = 20;
    int buttonWidth = panelWidth - 20;
    int buttonX = window.getWidth() - wholeWidth + 10;

    // Delete button
    DeleteButton = Rect(buttonX + 10, 10, buttonWidth, buttonHeight);
    DeleteButton.clickable = false;
}

void Panel::update() {
    int x, y;
    get_mouse_position(x, y);

    // check if the mouse is on the bar, the bar's wholeWidth is 10 pixels
    if (x >= window.getWidth() - wholeWidth && x <= window.getWidth() - wholeWidth + barWidth) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
        if (is_mouse_button_pressed(SDL_BUTTON_LEFT)) {
            draggingBar = true;
        }
    } else {
        // if the mouse is not on the bar, change the cursor to the default cursor
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    }

    if (draggingBar) {
        wholeWidth = window.getWidth() - x;
        panelWidth = wholeWidth - barWidth;
        buttonHandler();
    }

    if (is_mouse_button_released(SDL_BUTTON_LEFT)) {
        draggingBar = false;
    }

    handleEvents();

}


void Panel::handleEvents() {
    // check if any vectors are selected
    if (dataProxy.getSelectedVectors().size() > 0) {
        DeleteButton.clickable = true;
    } else {
        DeleteButton.clickable = false;
    }
    // check if the mouse is on the delete button
    int x, y;
    get_mouse_position(x, y);
    if (DeleteButton.contains(x, y) && DeleteButton.clickable) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        if (is_mouse_button_pressed(SDL_BUTTON_LEFT)) {
            dataProxy.addDeleteVectors(dataProxy.getSelectedVectors());
        }
    }
}

void Panel::draw() {
    // Draw panel
    //215, 217, 224
    SDL_SetRenderDrawColor(window.getRenderer(), 215, 217, 224, 225);
    window.fillRect(window.getWidth() - wholeWidth, 0, wholeWidth, window.getHeight(), Color(215, 217, 224, 225));

    // Draw border
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    window.drawRect(window.getWidth() - wholeWidth + 10, 0, wholeWidth - 10, window.getHeight(), Color(0, 0, 0, 255));

    // draw a bar to change size
    SDL_SetRenderDrawColor(window.getRenderer(), 50, 50, 50, 255);
    window.fillRect(window.getWidth() - wholeWidth, 0, barWidth, window.getHeight(), Color(50, 50, 50, 255));
    // one white line on the bar
    SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
    window.fillRect(window.getWidth() - wholeWidth + (barWidth / 2), (window.getHeight() / 2) - 13, 1, 25, Color(255, 255, 255, 255));

    // Draw buttons
    // Delete button
    window.fillRect(DeleteButton.x, DeleteButton.y, DeleteButton.w, DeleteButton.h, Color(255, 255, 255, 255));
    if (DeleteButton.clickable) {
        window.drawText("Delete vectors", DeleteButton.x + 5, DeleteButton.y + 3, 15, true, Color(0, 0, 0, 255));
    } else {
        window.drawText("Delete vectors", DeleteButton.x + 5, DeleteButton.y + 3, 15, true, Color(150, 150, 150, 255));
    }

}


void Panel::cleanUp() {

}
