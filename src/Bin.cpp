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

void Bin::serialize(std::ofstream &outputFile) const
{
    JsonWriter j;

    outputFile << "        {\n";
    outputFile << j.writeLine("width", std::to_string(this->getWidth()), false, 1);
    outputFile << j.writeLine("height", std::to_string(this->getHeight()), false, 1);
    outputFile << "            \"items\": [\n";
    bool first = true;
    for (const auto &item : items)
    {
        std::cout << "aaaaa";
        if (!first)
        {
            outputFile << ",\n";
        }
        item.serialize(outputFile);
        first = false;
    }
    outputFile << "\n            ]\n";
    outputFile << "        }";
}

void Bin::addItem(Item i)
{
    items.push_back(i);
}

//bool Bin::fit(Coordinate c, Item i) //on check les coordonnées en haut à gauche et on teste si ça rentre 

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


