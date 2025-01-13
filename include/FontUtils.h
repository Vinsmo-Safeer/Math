#ifndef MATH_FONTUTILS_H
#define MATH_FONTUTILS_H

#include <iostream>
#include <SDL_ttf.h>

class FontUtils {
public:
    // Function to measure the width of the text based on font size
    static int measureTextWidth(const char* text, int fontSize, TTF_Font* font) {
        int width;
        if (TTF_SizeText(font, text, &width, nullptr) != 0) {
            // Error measuring text width
            std::cout << "Failed to measure text width. Error: " << TTF_GetError() << std::endl;
            return 0;
        }
        return width;
    }
};

#endif //MATH_FONTUTILS_H
