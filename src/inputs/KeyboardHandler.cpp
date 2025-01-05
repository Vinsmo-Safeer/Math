#include <map>
#include "KeyboardHandler.h"

// Track key states and release events
static std::map<SDL_Keycode, bool> key_state;
static std::map<SDL_Keycode, bool> key_released;

void handleKeyInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        key_state[event.key.keysym.sym] = true;
        key_released[event.key.keysym.sym] = false; // Reset release flag
    }

    if (event.type == SDL_KEYUP) {
        key_state[event.key.keysym.sym] = false;
        key_released[event.key.keysym.sym] = true; // Set release flag
    }
}

bool is_key_pressed(SDL_Keycode key) {
    return key_state[key];
}

bool was_key_released(SDL_Keycode key) {
    // Check if the key was released, and reset the release state
    if (key_released[key]) {
        key_released[key] = false; // Reset after detecting
        return true;
    }
    return false;
}
