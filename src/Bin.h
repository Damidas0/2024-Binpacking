#ifndef BIN_H
#define BIN_H


#include "Rectangle.h"
#include<list>
#include"Item.h"
#include"JsonWriter.h"

class Bin : public Rectangle{
    private:
        std::list<Item> items; 
    public:
        Bin(int width, int height);
        
        int freeSpace() const;
        bool isFree(Coordinate c); 
        std::list<Coordinate> listFreeCoordinates() const;
};

#endif