// KeyboardHandler.h

#ifndef MATH_KEYBOARDHANDLER_H
#define MATH_KEYBOARDHANDLER_H



#include <SDL.h>
// Function to handle input events
void handleKeyInput(SDL_Event &event);

// Function to check if a specific key is pressed
bool is_key_pressed(SDL_Keycode key);




#endif //MATH_KEYBOARDHANDLER_H
