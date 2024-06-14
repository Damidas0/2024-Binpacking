#include "Bin.h"
#include <ostream>

#include"JsonWriter.h"
#include <iostream>
#include <fstream>
#include "Coordinate.h"

Bin::Bin(int width, int height) : Rectangle(width, height)
{
    for (int i = 0; i < height; i++)
    {
        std::vector<bool> temp;
        for (int j = 0; j < width; j++)
        {
            temp.push_back(true);
        }
        is_free.push_back(temp);
    }
}

int Bin::freeSpace() const
{
    int res = 0;
    for (int i = 0; i < this->getWidth(); i++) //here the order doesnt matter but in theory it should be the other way around
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
    for (int y= c.getY(); y < c.getY() + it.getHeight(); y++)
    {
        for (int x = c.getX(); x < c.getX() + it.getWidth(); x++)
        {
            if (x >= getWidth() || y >= getHeight() || !is_free[y][x])
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
    for (int i = 0; i < this->getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            std::cout << is_free[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Bin::add(Item i, Coordinate c)
{
    if (fit(c, i))
    {
        i.topLeft = c;
        items.push_back(i);
        for (int x = c.getX(); x < c.getX() + i.getWidth(); x++)
        {
            for (int y = c.getY(); y < c.getY() + i.getHeight(); y++)
            {
                is_free[y][x] = false; //works because it is inversed
            }
        }
    }
    else
    {
        std::cerr << "Item cannot be placed at the given coordinates : (" << c.getX() << ", " << c.getY() << ")\n";
    }
}


