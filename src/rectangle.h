#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    Rectangle(int x, int y);
    int getX() const;
    int getY() const;
private:
    int m_x;
    int m_y; 
};

#endif