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

    // An array of connected vectors
    std::vector<std::vector<Vec2D>> connectedVectors;

public:
    Matrix(Vec2D p_iHat, Vec2D p_jHat) : iHat(p_iHat), jHat(p_jHat) {
        twoDimensional = true;
    }
    // Matrix(Vec3D p_iHat, Vec3D p_jHat, Vec3D p_kHat) : iHat(p_iHat), jHat(p_jHat), kHat(p_kHat) {
    //     twoDimensional = false;
    // }

    void addVector(Vec2D vector) {
        for (int i = 0; i < vectors.size(); i++) {
            if (vectors[i] == vector) {
                return;
            }
        }
        vectors.push_back(vector);
        std::cout << "Vector added at " << vector.x << ", " << vector.y << std::endl;
    }

    void addConnectedVector(Vec2D vector1, Vec2D vector2) {
        // check if the vectors are already connected
        for (int i = 0; i < connectedVectors.size(); i++) {
            if (connectedVectors[i][0] == vector1 && connectedVectors[i][1] == vector2
                || connectedVectors[i][0] == vector2 && connectedVectors[i][1] == vector1) {
                return;
            }
        }
        std::vector<Vec2D> connectedVector;
        connectedVector.push_back(vector1);
        connectedVector.push_back(vector2);
        connectedVectors.push_back(connectedVector);
    }

    Vec2D& getVector(float x, float y) {
        // get this vector from the vectors
        for (int i = 0; i < vectors.size(); i++) {
            if (vectors[i].x == x && vectors[i].y == y) {
                return vectors[i];
            }
        }
    }

    std::vector<Vec2D> getVectors() {
        return vectors;
    }

    // void addVector(Vec3D vector) {
    //     vectors.push_back(vector);
    // }

    bool isTwoDimensional() { return twoDimensional; }
};


#endif //MATH_MATRIX_H
