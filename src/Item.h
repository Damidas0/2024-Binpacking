#pragma once
#include "Rectangle.h"
#include "Coordinate.h"
#include <ostream>

class Item : public Rectangle {
    public: 
        Item(int width, int height, int id);
        //Bin *belongsTo; 
        /**
         * @brief coordonnée en haut à gauche de l'item qui définit sa position dans le bin
         */
        Coordinate topLeft;
        /**
         * @brief id de l'item
         */
        int m_id; 
        /**
         * @brief Inverse la largeur et la hauteur de l'item
         
         */
        void rotate();

        friend std::ostream &operator<<(std::ostream &out, const Item& i);
        void serialize(std::ofstream& outputFile) const;

    private:

};