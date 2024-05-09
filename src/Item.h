#pragma once
#include "Rectangle.h"
#include "Coordinate.h"
#include "Bin.h"
#include <ostream>
#include<jsoncpp/json/json.h>

class Item : public Rectangle {
    public: 
        Item(int width, int height, int id);
        Bin *belongsTo; 
        Coordinate topLeft;
        int m_id; 

        void rotate();

        friend std::ostream &operator<<(std::ostream &out, const Item& i);
        Json::Value serialize() const;

    private:

};