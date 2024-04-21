#include "Rectangle.h"    

Rectangle::Rectangle(int width, int height)
    : m_width(width), m_height(height) {}

int Rectangle::getWidth() const {
    return m_width;
}
int Rectangle::getHeight() const{
    return m_height; 
}
void Rectangle::setWidth(int width) {
    m_width = width;
}
void Rectangle::setHeight(int height) {
    m_height = height;
}

