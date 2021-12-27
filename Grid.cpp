//
// Created by alvina on 26.12.21.
//

#include <algorithm>
#include "Grid.h"

using namespace std;

Grid::Grid(int mWight, int mHeight) : m_wight(mWight), m_height(mHeight) {

}

Grid::~Grid() {

}

const vector<Entity> &Grid::getWalls() const {
    return m_walls;
}

void Grid::setWalls(const vector<Entity> &walls) {
    Grid::m_walls = walls;
}

bool Grid::inBounds(Entity entity) {
    if (entity.m_x >= 0 && entity.m_x < m_wight && entity.m_y >= 0 && entity.m_y < m_height) {
        return true;
    } else {
        return false;
    }
}

bool Grid::isNotWall(Entity entity) {
    for (auto item : m_walls) {
        if (item.m_x == entity.m_x && item.m_y == entity.m_y) {
            return false;
        }
    }
    return true;
}

vector<Entity> Grid::neighbors(Entity entity) {
    vector<Entity> result;
    vector<Entity> nei = {{-1, 0},
                          {1,  0},
                          {0,  -1},
                          {0,  1}};
    for (auto item : nei) {
        if (isNotWall({entity.m_x + item.m_x, entity.m_y + item.m_y}) &&
            inBounds({entity.m_x + item.m_x, entity.m_y + item.m_y})) {
            result.push_back({entity.m_x + item.m_x, entity.m_y + item.m_y});
        }
    }
    if((entity.m_y + entity.m_x) % 2 == 0 ){
        reverse(result.begin(), result.end());
    }

        return result;
    }

    int Grid::getMWight() const {
        return m_wight;
    }

    int Grid::getMHeight() const {
        return m_height;
    }


    void Grid::setStart(const Entity &start) {
        Grid::start = start;
    }

    void Grid::setFinish(const Entity &finish) {
        Grid::finish = finish;
    }

    const Entity &Grid::getStart() const {
        return start;
    }

    const Entity &Grid::getFinish() const {
        return finish;
    }
