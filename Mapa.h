//
// Created by alvina on 25.12.21.
//

#ifndef SEMESTALNI_PRACE_PJC_MAPA_H
#define SEMESTALNI_PRACE_PJC_MAPA_H


#include <vector>
#include "Entity.h"
using namespace std;
class Mapa {
private:
    Entity start;
    vector< vector<Entity> > matrix;
    vector<Entity> neighbors;
    int m_max;
    int m_start_x;
    int m_start_y;

public:
    Mapa(vector<vector<Entity>> &matrix);

    virtual ~Mapa();

    const vector<vector<Entity>> &getMatrix();

    int getMMax();

    int getMStartX();

    int getMStartY();

    void setMatrix(vector<vector<Entity>> &matrix);

    void setMMax(int mMax);

    void setMStartX(int mStartX);

    void setMStartY(int mStartY);

    const Entity &getStart() const;

    void setStart(const Entity &start);

    const vector<Entity> &getNeighbors() const;

    void setNeighbors(const vector<Entity> &neighbors);


};


#endif //SEMESTALNI_PRACE_PJC_MAPA_H
