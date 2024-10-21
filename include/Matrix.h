#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <iostream>
#include "vector"
#include "Vec2D.h"

class Matrix {
private:
    bool twoDimensional = true;

    Vec2D origin = Vec2D(0, 0);
    // Vec3D origin = Vec3D(0, 0, 0);

    Vec2D iHat = Vec2D(1, 0);
    Vec2D jHat = Vec2D(0, 1);
    // Vec3D iHat = Vec3D(1, 0, 0);
    // Vec3D jHat = Vec3D(0, 1, 0);
    // Vec3D kHat = Vec3D(0, 0, 1);

    std::vector<Vec2D> vectors;
    // std::vector<Vec3D> vectors;
public:
    Matrix(Vec2D p_iHat, Vec2D p_jHat) : iHat(p_iHat), jHat(p_jHat) {
        twoDimensional = true;
    }
    // Matrix(Vec3D p_iHat, Vec3D p_jHat, Vec3D p_kHat) : iHat(p_iHat), jHat(p_jHat), kHat(p_kHat) {
    //     twoDimensional = false;
    // }

    void addVector(Vec2D vector) {
        vectors.push_back(vector);
    }

    // void addVector(Vec3D vector) {
    //     vectors.push_back(vector);
    // }

    bool isTwoDimensional() { return twoDimensional; }
};


#endif //MATH_MATRIX_H
