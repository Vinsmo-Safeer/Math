// PopUpMenu.cpp

/////////////////////////////////////////////
///////STILL IN PROGRESS/////////////////////
/////////////////////////////////////////////

#include "PopUpMenu.h"

PopUpMenu::PopUpMenu(int p_x, int p_y, std::string p_type)
    : x(p_x), y(p_y), type(p_type) {

    if (type == "rightClick") { rightClick(x, y); }
    else if (type == "selectedRightClick") {}
    else if (type == "create") {}
}

void PopUpMenu::rightClick(int x, int y) {
    visible = true; // Make the popup menu visible
    menuItems = { "Option 1", "Option 2", "Option 3" }; // Add some options
    menuRect = { x, y, 150, static_cast<int>(menuItems.size() * 30) }; // Adjust height based on items
}

void PopUpMenu::render(SDL_Renderer* renderer) {
    if (!visible) return;

    // Draw menu background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Dark gray
    SDL_RenderFillRect(renderer, &menuRect);

    // Draw menu border
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light gray
    SDL_RenderDrawRect(renderer, &menuRect);

    // Render menu items
    for (size_t i = 0; i < menuItems.size(); i++) {
        int itemY = menuRect.y + static_cast<int>(i * 30);
        SDL_Rect itemRect = { menuRect.x, itemY, menuRect.w, 30 };

        // Draw item background
        SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255); // Slightly lighter gray
        SDL_RenderFillRect(renderer, &itemRect);

        // Render text (placeholder, replace with actual text rendering code)
        // e.g., use SDL_ttf or a bitmap font system
        // renderText(renderer, menuItems[i], itemRect.x + 10, itemY + 5);

        // Draw item border
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Dark border
        SDL_RenderDrawRect(renderer, &itemRect);
    }
}

void PopUpMenu::handleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // Check if click is inside the popup menu
        if (visible && mouseX >= menuRect.x && mouseX <= (menuRect.x + menuRect.w) &&
            mouseY >= menuRect.y && mouseY <= (menuRect.y + menuRect.h)) {

            // Calculate which menu item was clicked
            int index = (mouseY - menuRect.y) / 30;
            if (index >= 0 && index < static_cast<int>(menuItems.size())) {
                std::cout << "Selected: " << menuItems[index] << std::endl;
                visible = false; // Close menu after selection
            }
        } else {
            // Click outside menu: hide it
            visible = false;
        }
    }
}
