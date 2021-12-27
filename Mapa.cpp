//
// Created by alvina on 25.12.21.
//

#include "Mapa.h"

Mapa::Mapa(vector<vector<Entity>> &matrix) : matrix(matrix) {}

Mapa::~Mapa() {

}

const vector<vector<Entity>> &Mapa::getMatrix() {
    return matrix;
}

int Mapa::getMMax() {
    return m_max;
}

int Mapa::getMStartX(){
    return m_start_x;
}

int Mapa::getMStartY() {
    return m_start_y;
}

void Mapa::setMatrix(vector<vector<Entity>> &matrix) {
    Mapa::matrix = matrix;
}

void Mapa::setMMax(int mMax) {
    m_max = mMax;
}

void Mapa::setMStartX(int mStartX) {
    m_start_x = mStartX;
}

void Mapa::setMStartY(int mStartY) {
    m_start_y = mStartY;
}

const Entity &Mapa::getStart() const {
    return start;
}

void Mapa::setStart(const Entity &start) {
    Mapa::start = start;
}

const vector<Entity> &Mapa::getNeighbors() const {
    return neighbors;
}

void Mapa::setNeighbors(const vector<Entity> &neighbors) {
    Mapa::neighbors = neighbors;
}
