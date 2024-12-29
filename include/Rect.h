#ifndef MATH_RECT_H
#define MATH_RECT_H

#include <string>

class Rect {
public:
    float x, y, w, h;
    bool clickable = false;

    Rect() : x(0), y(0), w(0), h(0) {}

    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    bool contains(float x, float y) {
        if (x > this->x && x < this->x + w && y > this->y && y < this->y + h) {
            return true;
        }
        return false;
    }


    Rect getRect() {
        return Rect(x, y, w, h);
    }
};

#endif //MATH_RECT_H
