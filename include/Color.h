#ifndef MATH_COLOR_H
#define MATH_COLOR_H

class Color {
public:
    int r, g, b, a;

    // Constructor
    Color(int red, int green, int blue, int alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}

    // Predefined common colors
    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color White() { return Color(255, 255, 255); }
    static Color Black() { return Color(0, 0, 0); }
    static Color Yellow() { return Color(255, 255, 0); }
    static Color Cyan() { return Color(0, 255, 255); }
    static Color Magenta() { return Color(255, 0, 255); }
    static Color Gray() { return Color(128, 128, 128); }
    static Color Orange() { return Color(255, 165, 0); }
    static Color Purple() { return Color(128, 0, 128); }
    static Color Teal() { return Color(0, 128, 128); }
    static Color Maroon() { return Color(128, 0, 0); }
    static Color Olive() { return Color(128, 128, 0); }
    static Color Navy() { return Color(0, 0, 128); }
    static Color DarkRed() { return Color(139, 0, 0); }
    static Color DarkGreen() { return Color(0, 100, 0); }
    static Color DarkBlue() { return Color(0, 0, 139); }
    static Color DarkYellow() { return Color(139, 139, 0); }
    static Color DarkCyan() { return Color(0, 139, 139); }
    static Color DarkMagenta() { return Color(139, 0, 139); }
    static Color DarkGray() { return Color(169, 169, 169); }
    static Color LightGray() { return Color(211, 211, 211); }
    static Color LightRed() { return Color(255, 69, 0); }
    static Color LightGreen() { return Color(144, 238, 144); }
    static Color LightBlue() { return Color(173, 216, 230); }
    static Color LightYellow() { return Color(255, 255, 224); }
    static Color LightCyan() { return Color(224, 255, 255); }
    static Color LightMagenta() { return Color(255, 224, 255); }
    static Color Transparent() { return Color(0, 0, 0, 0); }
};

#endif //MATH_COLOR_H
