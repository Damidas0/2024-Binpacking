#include <iostream>
#include "Coordinate.h"

Coordinate::Coordinate(double x, double y)
    : m_x(x), m_y(y) {}

double Coordinate::getX() const {
    return m_x;
}

double Coordinate::getY() const {
    return m_y;
}

void Coordinate::setX(double x) {
    m_x = x;
}

void Coordinate::setY(double y) {
    m_y = y;
}