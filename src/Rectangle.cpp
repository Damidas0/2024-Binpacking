#include Rectangle.h    

Rectangle::Rectangle(int width, int height)
    : m_width(width), m_height(height) {}

Rectangle::getWidth() const {
    return m_width;
}
Rectangle::getHeight() const{
    return m_height; 
}


