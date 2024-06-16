#pragma once
#include "Bin.h"
#include "Coordinate.h"

class FreeSpace: public Bin
{
private:
    /* data */
public: 
    FreeSpace(int width, int height, Coordinate topLeft);
    /**
     * Flag to know if this free space is wasted space or usable space
     */
    bool wastedSpace; 
    Coordinate topLeft;

     /**
     * @brief fonction qui ajoute un item dans la bin
     * on a pas besoin des coordonnée parce qu'on place toujours en haut à gauche du fs 
     */
    void add(Item i); 


};
