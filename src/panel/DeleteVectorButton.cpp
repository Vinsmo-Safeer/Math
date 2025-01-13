#include "DeleteVectorButton.h"

DeleteVectorButton::DeleteVectorButton(DataProxy& p_dataProxy, RenderWindow& p_window) : dataProxy(p_dataProxy), window(p_window), PanelButtons(p_window) {
    text = "Delete Vectors";
    clickable = true;
    toggled = false;
    buttonRect = Rect(0, 0, 0, 0);
}

void DeleteVectorButton::update(int mouseX, int mouseY) {

    clickable = dataProxy.getSelectedVectors().size() > 0;

    if (buttonRect.w !=0 && buttonRect.h != 0 && buttonRect.x > 1 && buttonRect.y > 1) {
        if (buttonRect.contains(mouseX, mouseY)) {
            if (clickable) {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                if (dataProxy.leftButtonReleased) {
                    dataProxy.setDeleteVectors(dataProxy.getSelectedVectors());
                }
            } else {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO));
            }
        }
    }
}
