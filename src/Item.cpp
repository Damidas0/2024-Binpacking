#include "Item.h"
#include "Coordinate.h"
#include"Bin.h"
#include"JsonWriter.h"
#include <iostream>
#include <fstream>

Item::Item(int id, int width, int height) : Rectangle(width, height), topLeft(0, 0), m_id(id) { // il faudra voir si on peut passer belongTo en paramètre
    //belongsTo = nullptr;
}
void Item::rotate() {
    int temp = getWidth();
    setWidth(getHeight());
    setHeight(temp);
}

void Item::serialize(std::ofstream& outputFile)  const{
    
    JsonWriter j;
    outputFile  << "        {\n";
    outputFile  << j.writeLine("id", std::to_string(m_id), false, 1);
    outputFile  << j.writeLine("width", std::to_string(getWidth()), false, 1);
    outputFile  << j.writeLine("height", std::to_string(getHeight()), true, 1);
    outputFile  << "        }";
}

std::ostream &operator<<(std::ostream &out, const Item& i)
{
    out << i.m_id << " : " << i.getWidth() << "x" << i.getHeight();
    return out;
}
