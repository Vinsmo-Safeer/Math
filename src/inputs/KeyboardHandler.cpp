// KeyboardHandler.cpp

#include <map>
#include "KeyboardHandler.h"

static std::map<SDL_Keycode, bool> key_state;

void handleKeyInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        key_state[event.key.keysym.sym] = true;
    }

    if (event.type == SDL_KEYUP) {
        key_state[event.key.keysym.sym] = false;
    }
}

bool is_key_pressed(SDL_Keycode key) {
    return key_state[key];
}