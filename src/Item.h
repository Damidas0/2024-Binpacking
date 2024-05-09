#pragma once
#include "Rectangle.h"
#include "Coordinate.h"
#include "Bin.h"
#include <ostream>


class Item : public Rectangle {
    public: 
        Item(int width, int height, int id);
        Bin *belongsTo; 
        Coordinate topLeft;
        int m_id; 

        void rotate();

        friend std::ostream &operator<<(std::ostream &out, const Item& i);


    private:

};