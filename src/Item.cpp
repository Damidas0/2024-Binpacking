#include "Item.h"
#include "Coordinate.h"
#include"Bin.h"

Item::Item(int id, int width, int height) : Rectangle(width, height), topLeft(0, 0), m_id(id) { // il faudra voir si on peut passer belongTo en paramètre
    belongsTo = nullptr;
}
void Item::rotate() {
    int temp = getWidth();
    setWidth(getHeight());
    setHeight(temp);
}

std::ostream &operator<<(std::ostream &out, const Item& i)
{
    out << i.m_id << " : " << i.getWidth() << "x" << i.getHeight();
    return out;
}
