#ifndef MATH_VEC2D_H
#define MATH_VEC2D_H

#include <cmath>

class Vec2D {
public:
    float x, y;

    Vec2D() : x(0), y(0) {}

    Vec2D(float p_x, float p_y) : x(p_x), y(p_y) {}

    Vec2D operator+(const Vec2D& other) {
        return Vec2D(x + other.x, y + other.y);
    }
    Vec2D operator-(const Vec2D& other) {
        return Vec2D(x - other.x, y - other.y);
    }
    Vec2D operator*(const float& scalar) {
        return Vec2D(x * scalar, y * scalar);
    }
    Vec2D operator/(const float& scalar) {
        return Vec2D(x / scalar, y / scalar);
    }
    Vec2D operator+=(const Vec2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    // for Vec2D == Vec2D
    bool operator==(const Vec2D& other) {
        return x == other.x && y == other.y;
    }


    void print() const {
        std::cout << "x: " << x << " y: " << y << std::endl;
    }

};

#endif //MATH_VEC2D_H
