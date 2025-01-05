#include "DataProxy.h"

DataProxy::DataProxy() {
    deleteVectors = std::vector<Vec2D>();
    selectedVectors = std::vector<Vec2D>();
}

void DataProxy::setDeleteVector(Vec2D vector) {
    deleteVectors = {vector};
}
void DataProxy::setDeleteVectors(std::vector<Vec2D> vectors) {
    deleteVectors.assign(vectors.begin(), vectors.end());
}

void DataProxy::removeDeleteVector(Vec2D vector) {
    auto it = std::find(deleteVectors.begin(), deleteVectors.end(), vector);
    if (it != deleteVectors.end()) {
        deleteVectors.erase(it);
    }
}

std::vector<Vec2D> DataProxy::getDeleteVectors() {
    return deleteVectors;
}

void DataProxy::clearDeleteVectors() {
    deleteVectors.clear();
}

void DataProxy::setSelectedVector(Vec2D vector) {
    selectedVectors = {vector};
}
void DataProxy::setSelectedVectors(std::vector<Vec2D> vectors) {
    selectedVectors.assign(vectors.begin(), vectors.end());
}

void DataProxy::removeSelectedVector(Vec2D vector) {
    auto it = std::find(selectedVectors.begin(), selectedVectors.end(), vector);
    if (it != selectedVectors.end()) {
        selectedVectors.erase(it);
    }
}

std::vector<Vec2D> DataProxy::getSelectedVectors() {
    return selectedVectors;
}

void DataProxy::clearSelectedVectors() {
    selectedVectors.clear();
}

void DataProxy::clearAll() {
    deleteVectors.clear();
    selectedVectors.clear();
    std::cout << "All vectors cleared." << std::endl;
}