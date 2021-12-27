//
// Created by alvina on 25.12.21.
//
#include <vector>

#ifndef SEMESTALNI_PRACE_PJC_RESULT_H
#define SEMESTALNI_PRACE_PJC_RESULT_H

using namespace std;
class Result {
private:
    vector<int> m_x;
    vector<int> m_y;
    int steps;

public:
    Result();

    virtual ~Result();

    const vector<int> &getMX() const;

    void setMX(const vector<int> &mX);

    const vector<int> &getMY() const;

    void setMY(const vector<int> &mY);

    int getSteps() const;

    void setSteps(int steps);

};


#endif //SEMESTALNI_PRACE_PJC_RESULT_H
