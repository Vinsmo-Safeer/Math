#include "DataProxy.h"

DataProxy::DataProxy() {
    deleteVectors = std::vector<Vec2D>();
    selectedVectors = std::vector<Vec2D>();
}

void DataProxy::addDeleteVector(Vec2D vector) {
    deleteVectors.push_back(vector);
}
void DataProxy::addDeleteVectors(std::vector<Vec2D> vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        deleteVectors.push_back(vectors[i]);
    }
}

void DataProxy::removeDeleteVector(Vec2D vector) {
    for (int i = 0; i < deleteVectors.size(); i++) {
        if (deleteVectors[i] == vector) {
            deleteVectors.erase(deleteVectors.begin() + i);
            break;
        }
    }
}

std::vector<Vec2D> DataProxy::getDeleteVectors() {
    return deleteVectors;
}

void DataProxy::clearDeleteVectors() {
    deleteVectors.clear();
}

void DataProxy::addSelectedVector(Vec2D vector) {
    selectedVectors.push_back(vector);
}
void DataProxy::addSelectedVectors(std::vector<Vec2D> vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        selectedVectors.push_back(vectors[i]);
    }
}

void DataProxy::removeSelectedVector(Vec2D vector) {
    for (int i = 0; i < selectedVectors.size(); i++) {
        if (selectedVectors[i] == vector) {
            selectedVectors.erase(selectedVectors.begin() + i);
            break;
        }
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
}