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

    void removeVector(Vec2D vector) {
        std::cout << "Attempting to remove vector: (" << vector.x << ", " << vector.y << ")" << std::endl;

        // Check and remove the vector itself
        for (size_t i = 0; i < vectors.size(); i++) {
            std::cout << "Checking vector at index " << i << ": ("
                      << vectors[i].x << ", " << vectors[i].y << ")" << std::endl;
            if (vectors[i] == vector) {
                std::cout << "Vector match found at index " << i << ". Removing it." << std::endl;
                vectors.erase(vectors.begin() + i);
                std::cout << "Vector removed successfully." << std::endl;

                // Check and remove any connected vectors
                for (size_t i = 0; i < connectedVectors.size(); i++) {
                    const auto& connection = connectedVectors[i];
                    std::cout << "Checking connected vector pair at index " << i << ": [("
                              << connection[0].x << ", " << connection[0].y << "), ("
                              << connection[1].x << ", " << connection[1].y << ")]" << std::endl;

                    if (connection[0] == vector || connection[1] == vector) {
                        std::cout << "Connected vector pair involving (" << vector.x << ", " << vector.y
                                  << ") found at index " << i << ". Removing it." << std::endl;
                        connectedVectors.erase(connectedVectors.begin() + i);
                        std::cout << "Connected vector pair removed successfully." << std::endl;
                        i--; // Adjust index after removal
                    }
                }

                return;
            }
        }
        std::cout << "Vector not found in 'vectors'." << std::endl;


    }



    void addConnectedVector(Vec2D vector1, Vec2D vector2) {
        if (isConnected(vector1, vector2)) {
            return; // Connection already exists
        }
        connectedVectors.push_back({vector1, vector2});
        std::cout << "Connected vector added at "
                  << vector1.x << ", " << vector1.y << " and "
                  << vector2.x << ", " << vector2.y << std::endl;
    }


    bool isConnected(const Vec2D& vector1, const Vec2D& vector2) {
        for (const auto& connection : connectedVectors) {
            if ((connection[0] == vector1 && connection[1] == vector2) ||
                (connection[0] == vector2 && connection[1] == vector1)) {
                return true;
            }
        }
        return false;
    }


    std::vector<std::vector<Vec2D>> getConnectedVectors() {
        return connectedVectors;
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

    void moveVector(Vec2D vector, float x, float y) {
        // change the x and y of the vector in vectors
        for (int i = 0; i < vectors.size(); i++) {
            if (vectors[i] == vector) {
                vectors[i].x = x;
                vectors[i].y = y;
            }
        }
        // change the x and y of the vector in connectedVectors
        for (int i = 0; i < connectedVectors.size(); i++) {
            if (connectedVectors[i][0] == vector) {
                connectedVectors[i][0].x = x;
                connectedVectors[i][0].y = y;
            }
            if (connectedVectors[i][1] == vector) {
                connectedVectors[i][1].x = x;
                connectedVectors[i][1].y = y;
            }
        }
    }

    void moveVector(Vec2D vector, Vec2D newVector) {
        // change the x and y of the vector in vectors
        for (int i = 0; i < vectors.size(); i++) {
            if (vectors[i] == vector) {
                vectors[i] = newVector;
            }
        }
        // change the x and y of the vector in connectedVectors
        for (int i = 0; i < connectedVectors.size(); i++) {
            if (connectedVectors[i][0] == vector) {
                connectedVectors[i][0] = newVector;
            }
            if (connectedVectors[i][1] == vector) {
                connectedVectors[i][1] = newVector;
            }
        }
    }

    // void addVector(Vec3D vector) {
    //     vectors.push_back(vector);
    // }

    bool isTwoDimensional() { return twoDimensional; }
};


#endif //MATH_MATRIX_H
