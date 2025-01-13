#include "Panel.h"

Panel::Panel(RenderWindow& p_window, DataProxy &p_dataProxy) :
window(p_window), dataProxy(p_dataProxy),

deleteButton(p_dataProxy, p_window),
connectButton(p_dataProxy, p_window)
{
    std::cout << "Panel created." << std::endl;
    int w, h;
    SDL_GetWindowSize(window.getWindow(), &w, &h);
    std::cout << "Window size: " << w << "x" << h << std::endl;


    buttons.push_back(&deleteButton);
    buttons.push_back(&connectButton);

    setPanelWidth(w * 0.2);

}

void Panel::setPanelWidth(int width) {
    wholeWidth = width;
    wholePanelRect.x = window.getWidth() - wholeWidth;
    wholePanelRect.w = wholeWidth;
    wholePanelRect.h = window.getHeight();
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

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->buttonRect = Rect(buttonX + 10, 10 + (30 * i), buttonWidth, buttonHeight);
    }
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
    } else if (wholePanelRect.contains(x, y)) {
        // if the mouse is not on the bar, change the cursor to the default cursor
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    }

    if (draggingBar) {
        wholeWidth = window.getWidth() - x;
        panelWidth = wholeWidth - barWidth;
        dataProxy.panelWidth = wholeWidth;
        buttonHandler();
    }

    if (is_mouse_button_released(SDL_BUTTON_LEFT)) {
        draggingBar = false;
    }

    handleEvents();


}


void Panel::handleEvents() {

    int x, y;
    get_mouse_position(x, y);


    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->update(x, y);
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

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->draw();
    }

}


void Panel::cleanUp() {

}
