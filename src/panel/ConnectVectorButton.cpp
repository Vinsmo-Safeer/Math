#include "ConnectVectorButton.h"

ConnectVectorButton::ConnectVectorButton(DataProxy& p_dataProxy, RenderWindow&p_window) : dataProxy(p_dataProxy), window(p_window), PanelButtons(p_window) {
    text = "Connect Vectors";
    clickable = true;
    toggled = false;
    buttonRect = Rect(0, 0, 0, 0);
}

void ConnectVectorButton::update(int mouseX, int mouseY) {

    toggled = dataProxy.connectVectors;

    if (buttonRect.w !=0 && buttonRect.h != 0 && buttonRect.x > 1 && buttonRect.y > 1) {
        if (buttonRect.contains(mouseX, mouseY)) {
            if (clickable) {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                if (dataProxy.leftButtonReleased) {
                    dataProxy.connectVectors = !dataProxy.connectVectors;
                }
            } else {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO));
            }
        }
    }
}