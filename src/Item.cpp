#include "Item.h"
#include "Coordinate.h"
#include"Bin.h"

Item::Item(int width, int height) : Rectangle(width, height), bottomLeft(0, 0) { // il faudra voir si on peut passer belongTo en paramètre
    belongsTo = nullptr;
    bottomLeft = Coordinate(0, 0);
}
void Item::rotate() {
    int temp = getWidth();
    setWidth(getHeight());
    setHeight(temp);
}