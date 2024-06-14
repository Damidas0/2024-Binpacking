#include "Bin.h"
#include <ostream>

#include"JsonWriter.h"
#include <iostream>
#include <fstream>
#include "Coordinate.h"

Bin::Bin(int width, int height) : Rectangle(width, height)
{
    for (int i = 0; i < width; i++)
    {
        std::vector<bool> temp;
        for (int j = 0; j < height; j++)
        {
            temp.push_back(true);
        }
        is_free.push_back(temp);
    }
}

int Bin::freeSpace() const
{
    int res = 0;
    for (int i = 0; i < this->getWidth(); i++)
    {
        for (int j = 0; j < getHeight(); j++)
        {
            if (is_free[i][j])
            {
                res++;
            }
        }
    }
    return res;
}

bool Bin::fit(Coordinate c, Item it)
{
    for (int i = c.getX(); i < c.getX() + it.getWidth(); i++)
    {
        for (int j = c.getY(); j < c.getY() + it.getHeight(); j++)
        {
            if (this->is_free[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool Bin::fitRotate(Coordinate c, Item i) //l'objet I ne doit pas être modifié 
{
    Item rotatedItem = i; // Copie de l'objet i
    rotatedItem.rotate(); // Rotation de la copie
    return fit(c, rotatedItem); // Test de la copie
}

bool Bin::fitGlobal(Coordinate c, Item i, bool &rotate)
{
    if (fit(c, i))
    {
        rotate = false;
        return true;
    }
    else if (fitRotate(c, i))
    {
        rotate = true;
        return true;
    }
    return false;
}

void Bin::printIsFree() const
{
    for (int i = 0; i < this->getWidth(); i++)
    {
        for (int j = 0; j < getHeight(); j++)
        {
            std::cout << is_free[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


