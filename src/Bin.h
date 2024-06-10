#ifndef BIN_H
#define BIN_H


#include "Rectangle.h"
#include<list>
#include "Item.h"
#include"JsonWriter.h"

class Bin : public Rectangle{
    private:
        std::list<Item> items;
        std::vector<std::vector<bool>> is_free; // grille de disponibilité (bien la modifier quand on ajoute un item)
    public:
        Bin(int width, int height);
        int freeSpace() const;
        bool isFree(Coordinate c); 
        std::vector<Coordinate> listFreeCoordinates() const; 

};

#endif