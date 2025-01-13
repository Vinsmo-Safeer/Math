#ifndef MATH_PANELBUTTONS_H
#define MATH_PANELBUTTONS_H

#include <string>
#include "Rect.h"
#include "RenderWindow.h"

class PanelButtons {
public:

    RenderWindow& window;

    bool clickable;
    bool toggled;

    const char* text;

    Rect buttonRect;

    PanelButtons(RenderWindow& p_window)
            : window(p_window), text(), clickable(false), toggled(false), buttonRect(Rect(0, 0, 0, 0)) {}

    virtual ~PanelButtons() = default; // Virtual destructor

    virtual void update(int mouseX, int mouseY) = 0;

    virtual void draw() {
        if (buttonRect.w <= 0 || buttonRect.h <= 0) {
            return;
        }

        // if clickable, color = black, else color = gray
        // if toggled, bg color = orange, else bg color = white

        Color bgColor = Color(255, 255, 255, 255);
        Color textColor = Color(0, 0, 0, 255);

        if (clickable) {
            if (toggled) {
                bgColor = Color(255, 165, 0, 255);
            } else {
                bgColor = Color(255, 255, 255, 255);
            }
            textColor = Color(0, 0, 0, 255);
        } else {
            bgColor = Color(192, 192, 192, 255);
            textColor = Color(128, 128, 128, 255);
        }

        // Draw the button background and border
        // the border should be the half alpha of the background
        window.fillRect(buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h, bgColor);
        window.drawRect(buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h, 2, calculateBorderColor(bgColor));


        if (text && text[0] != '\0') {
            // Calculate font size based on button height
            int fontSize = buttonRect.h / 1.5; // Example: Font size is half of button height

            // Calculate maximum width for text
            int maxTextWidth = buttonRect.w - 20; // Leave some padding on both sides

            // Measure text width
            int textWidth = window.measureTextWidth(text, fontSize);

            std::string displayText = text;

            // Truncate text if necessary
            if (textWidth > maxTextWidth) {
                while (!displayText.empty() && window.measureTextWidth(displayText.c_str(), fontSize) > maxTextWidth) {
                    displayText.pop_back();
                }
                displayText += "...";
            }

//            // Truncate text if necessary
//            if (textWidth > maxTextWidth) {
//                while (!displayText.empty() && window.measureTextWidth(displayText + "...", fontSize) > maxTextWidth) {
//                    displayText.pop_back();
//                }
//                displayText += "...";
//            }

            // Center text within the button
            int textX = buttonRect.x + (buttonRect.w - window.measureTextWidth(displayText.c_str(), fontSize)) / 2;
            int textY = buttonRect.y + (buttonRect.h - fontSize) / 2;

            // Draw the text
            window.drawText(displayText.c_str(), textX, textY, fontSize, false, textColor);
        }
    }

private:
Color calculateBorderColor(Color bgColor) {
        // Extract RGB values
        int r = bgColor.r;
        int g = bgColor.g;
        int b = bgColor.b;

        // Option 1: Darken the color for the border
        int darkeningFactor = 50;  // Darken by 50 for example
        r = std::max(0, r - darkeningFactor);
        g = std::max(0, g - darkeningFactor);
        b = std::max(0, b - darkeningFactor);

//        // Option 2: Lighten the color for the border
//        int lighteningFactor = 50;
//        r = std::min(255, r + lighteningFactor);
//        g = std::min(255, g + lighteningFactor);
//        b = std::min(255, b + lighteningFactor);


        return Color(r, g, b, bgColor.a);
    }
};

#endif //MATH_PANELBUTTONS_H
