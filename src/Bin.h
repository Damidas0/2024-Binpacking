#ifndef BIN_H
#define BIN_H


#include "Rectangle.h"
#include<list>
#include "Item.h"
#include"JsonWriter.h"
#include "Ennonce.h"

#include <ostream>

class Bin : public Rectangle{
    private:
        std::list<Item> items;
        std::vector<std::vector<bool>> is_free; // grille de disponibilité (bien la modifier quand on ajoute un item)
        
    public:

        Bin(int width, int height);
        void serialize(std::ofstream& outputFile) const;

        int freeSpace() const; //renvoi la place totale restante libre
        bool isFree(Coordinate c); 
        bool fit(Coordinate c, Item i); 
        //std::list<Coordinate> listFreeCoordinates() const;
        //int freeSpace() const;
        //bool isFree(Coordinate c); 
        std::list<Coordinate> listFreeCoordinates() const; 

};

#endif