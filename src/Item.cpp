#import "Item.h"
#import "Coordinate.h"
#import "Bin.h"
Item::Item(int width, int height, Coordinate bottomLeft, Bin belongsTo)
    : m_width(width), m_height(height) {}

void Item::rotate() {
    int temp = m_width;
    m_width = m_height;
    m_height = temp;
}