#ifndef BIN_H
#define BIN_H


#include "Rectangle.h"
#include<list>
#include"Item.h"
#include"JsonWriter.h"
#include "Ennonce.h"

#include <ostream>

class Bin : public Rectangle{
    private:
        std::list<Item> items; 
    public:
        Bin(int width, int , Ennonce e);

        void serialize(std::ofstream& outputFile) const;

        int freeSpace() const;
        bool isFree(Coordinate c); 
        bool fit(Coordinate c, Item i); 
        std::list<Coordinate> listFreeCoordinates() const;
};

#endif