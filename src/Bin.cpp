#include "Bin.h"
#include <ostream>

#include"JsonWriter.h"
#include <iostream>
#include <fstream>
#include "Coordinate.h"

Bin::Bin(int width, int height) : Rectangle(width, height)
{
    is_free.resize(width, std::vector<bool>(height, true));  // Initialize is_free grid

}

int Bin::freeSpace() const
{
    int freeCount = 0;
        for (const auto& row : is_free) {
            for (bool free : row) {
                if (free) {
                    freeCount++;
                }
            }
        }
    return freeCount;
}

bool Bin::fit(Item it)
{
    if (it.getWidth() > getWidth() || it.getHeight() > getHeight())
    {
        return false;
    }
    return true;
}

bool Bin::fitRotate(Item i) //l'objet I ne doit pas être modifié 
{
    if (i.getHeight() > getWidth() || i.getWidth() > getHeight())
    {
        return false;
    }
    return true;
}


bool Bin::fitGlobal(Item item, bool& rotate) 
{
    if (fit(item))
    {
        rotate = false;
        return true;
    }
    else if (fitRotate(item))
    {
        rotate = true;
        return true;
    }
    return false;
}



void Bin::printIsFree() const
{
    for (int i = 0; i < this->getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            std::cout << is_free[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Bin::add(Item item, Coordinate c)
{
    item.topLeft = c;
    items.push_back(item);
    for (int i = c.getX(); i < c.getX() + item.getWidth(); i++)
    {
        for (int j = c.getY(); j < c.getY() + item.getHeight(); j++)
        {
            is_free[i][j] = false;
        }
    }
    
}

