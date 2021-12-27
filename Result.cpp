//
// Created by alvina on 25.12.21.
//

#include "Result.h"

Result::Result(){}

Result::~Result() {

}

const vector<int> &Result::getMX() const {
    return m_x;
}

void Result::setMX(const vector<int> &mX) {
    m_x = mX;
}

const vector<int> &Result::getMY() const {
    return m_y;
}

void Result::setMY(const vector<int> &mY) {
    m_y = mY;
}

int Result::getSteps() const {
    return steps;
}

void Result::setSteps(int steps) {
    Result::steps = steps;
};
