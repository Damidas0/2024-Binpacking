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

