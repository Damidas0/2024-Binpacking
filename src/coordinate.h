#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
    Coordinate(double x, double y);

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
   
private:
    double m_x;
    double m_y;
};

#endif
