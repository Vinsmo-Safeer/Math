#include <map>
#include "MouseHandler.h"

static std::map<Uint8, bool> mouse_button_state;
static int mouse_x = 0;
static int mouse_y = 0;

void handleMouseInput(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        mouse_button_state[event.button.button] = true;
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        mouse_button_state[event.button.button] = false;
    }

    if (event.type == SDL_MOUSEMOTION) {
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;
    }
}

bool is_mouse_button_pressed(Uint8 button) {
    return mouse_button_state[button];
}

bool is_mouse_button_released(Uint8 button) {
    return !mouse_button_state[button];
}


void get_mouse_position(int &x, int &y) {
    x = mouse_x;
    y = mouse_y;
}