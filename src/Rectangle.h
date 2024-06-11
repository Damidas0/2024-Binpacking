#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:

    Rectangle(int width, int height);

    int getWidth() const;
    int getHeight() const;
    void setWidth(int width);
    void setHeight(int height);
    int getArea() const;
private:
    int m_width; 
    int m_height;
};

#endif