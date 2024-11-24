#ifndef MATH_POPUPMENU_H
#define MATH_POPUPMENU_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

/////////////////////////////////////////////
///////STILL IN PROGRESS/////////////////////
/////////////////////////////////////////////

class PopUpMenu {
private:
    bool visible = false;       // Whether the menu is visible
    int x, y;                   // Position of the popup menu
    std::string type;           // Type of the popup menu (e.g., "rightClick")
    SDL_Rect menuRect;          // Rectangle defining the menu bounds
    std::vector<std::string> menuItems; // List of menu items

public:
    // Constructor
    PopUpMenu(int p_x, int p_y, std::string p_type);

    // Show the popup menu
    void show(int p_x, int p_y) {
        x = p_x;
        y = p_y;
        visible = true;
    }

    // Hide the popup menu
    void hide() {
        visible = false;
    }

    // Check if the popup menu is currently visible
    bool isVisible() const {
        return visible;
    }

    // Initialize the menu for a right-click action
    void rightClick(int x, int y);

    // Render the popup menu
    void render(SDL_Renderer* renderer);

    // Handle events such as mouse clicks
    void handleEvent(SDL_Event& event);
};

#endif // MATH_POPUPMENU_H
