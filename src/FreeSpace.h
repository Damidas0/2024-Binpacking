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


};
