#include "Item.h"
#include "Coordinate.h"
#include"Bin.h"

Item::Item(int width, int height, int id) : Rectangle(width, height), topLeft(0, 0), m_id(id) { // il faudra voir si on peut passer belongTo en paramètre
    belongsTo = nullptr;
}
void Item::rotate() {
    int temp = getWidth();
    setWidth(getHeight());
    setHeight(temp);
}