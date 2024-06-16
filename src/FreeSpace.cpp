#include "FreeSpace.h"
#include <iostream>

/**
 * @brief constructeur
 * @param topleft coordonnées du coin supérieur gauche dans la bin
 */
FreeSpace::FreeSpace(int width, int height, Coordinate topLeft)
    : Bin(width, height), topLeft(topLeft) 
    {
        wastedSpace = false;
    }


