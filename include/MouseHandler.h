#ifndef MATH_MOUSEHANDLER_H
#define MATH_MOUSEHANDLER_H

#include <SDL.h>

void handleMouseInput(SDL_Event& event);

// Function to check if a specific mouse button is pressed
bool is_mouse_button_pressed(Uint8 button);

// Function to check if a specific mouse button is released
bool is_mouse_button_released(Uint8 button);

// Function to get the current mouse position
void get_mouse_position(int &x, int &y);

#endif //MATH_MOUSEHANDLER_H
