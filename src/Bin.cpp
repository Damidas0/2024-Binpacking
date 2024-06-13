#include "Bin.h"
#include <ostream>

#include"JsonWriter.h"
#include <iostream>
#include <fstream>
#include "Coordinate.h"

Bin::Bin(int width, int height) : Rectangle(width, height)
{
    this->is_free = std::vector<std::vector<bool>>(height, std::vector<bool>(width, true));
}



bool Bin::fit(Coordinate c, Item i) //on check les coordonnées en haut à gauche et on teste si ça rentre 
{
    for (int y = c.getY(); y < c.getY() + i.getHeight(); ++y)
    {
        for (int x = c.getX(); x < c.getX() + i.getWidth(); ++x)
        {
            if (x >= this->getWidth() || y >= this->getHeight() || !this->is_free[y][x])
            {
                return false;
            }
        }
    }

    return true;

}





int Bin::freeSpace() const {
    int width = this->getWidth();
    int height = this->getHeight();
    int free_space = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (this->is_free[y][x]) {
                free_space++;
            }
        }
    }
    return free_space;

}

bool Bin::isFree(Coordinate c) {
    return this->is_free[c.getY()][c.getX()];
}

void Bin::printIsFree() const {
    int width = this->getWidth();
    int height = this->getHeight();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << this->is_free[y][x] << " ";
        }
        std::cout << std::endl;
    }
}
