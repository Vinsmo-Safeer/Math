#ifndef MATH_DATAPROXY_H
#define MATH_DATAPROXY_H

#include <iostream>
#include <vector>
#include "Vec2D.h"

class DataProxy {
private:

    std::vector<Vec2D> deleteVectors;
    std::vector<Vec2D> selectedVectors;

public:

    int panelWidth = 0;

    DataProxy();
    void addDeleteVector(Vec2D vector);
    void addDeleteVectors(std::vector<Vec2D> vectors);
    void removeDeleteVector(Vec2D vector);
    void removeDeleteVectors(std::vector<Vec2D> vectors);
    std::vector<Vec2D> getDeleteVectors();
    void clearDeleteVectors();

    void addSelectedVector(Vec2D vector);
    void addSelectedVectors(std::vector<Vec2D> vectors);
    void removeSelectedVector(Vec2D vector);
    void removeSelectedVectors(std::vector<Vec2D> vectors);
    std::vector<Vec2D> getSelectedVectors();
    void clearSelectedVectors();

    void clearAll();

};

#endif //MATH_DATAPROXY_H
