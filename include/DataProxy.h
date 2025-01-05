#ifndef MATH_DATAPROXY_H
#define MATH_DATAPROXY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vec2D.h"

class DataProxy {
private:

    std::vector<Vec2D> deleteVectors;
    std::vector<Vec2D> selectedVectors;

public:

    int panelWidth = 0;

    bool connectVectors = false;

    bool leftButtonReleased = false;

    DataProxy();
    void setDeleteVector(Vec2D vector);
    void setDeleteVectors(std::vector<Vec2D> vectors);
    void removeDeleteVector(Vec2D vector);
    void removeDeleteVectors(std::vector<Vec2D> vectors);
    std::vector<Vec2D> getDeleteVectors();
    void clearDeleteVectors();

    void setSelectedVector(Vec2D vector);
    void setSelectedVectors(std::vector<Vec2D> vectors);
    void removeSelectedVector(Vec2D vector);
    void removeSelectedVectors(std::vector<Vec2D> vectors);
    std::vector<Vec2D> getSelectedVectors();
    void clearSelectedVectors();

    void clearAll();

};

#endif //MATH_DATAPROXY_H
