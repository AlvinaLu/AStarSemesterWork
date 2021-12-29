//
// Created by alvina on 26.12.21.
//

#ifndef SEMESTALNI_PRACE_PJC_GRID_H
#define SEMESTALNI_PRACE_PJC_GRID_H


#include <vector>
#include "Entity.h"
using namespace std;
class Grid {
private:
    int m_wight;
    int m_height;
    Entity start;
    Entity finish;
    vector<Entity> m_walls;
    vector<Entity> m_points;

public:
    Grid();
    Grid(int mWight, int mHeight);

    virtual ~Grid();

    const vector <Entity> &getWalls() const;

    void setWalls(const vector <Entity> &walls);

    bool inBounds(Entity entity);
    bool isNotWall(Entity entity);
    vector<Entity> neighbors(Entity entity);

    int getMWight() const;

    int getMHeight() const;

    void setMWight(int mWight);

    void setStart(const Entity &start);

    void setFinish(const Entity &finish);

    const Entity &getStart() const;

    const Entity &getFinish() const;

    const vector<Entity> &getMPoints() const;

    void setMPoints(const vector<Entity> &mPoints);


};


#endif //SEMESTALNI_PRACE_PJC_GRID_H
