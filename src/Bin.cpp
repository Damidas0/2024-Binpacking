#include "Bin.h"
#include <ostream>

#include"JsonWriter.h"
#include <iostream>
#include <fstream>

Bin::Bin(int width, int height, Ennonce e) : Rectangle(width, height)
{
}

void Bin::serialize(std::ofstream &outputFile) const
{
    outputFile << "        {\n";
    //outputFile << "            \"id\": \"" << getId() << "\",\n";
    outputFile << "            \"items\": [\n";
    bool first = true;
    for (const auto &item : items)
    {
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

bool Bin::fit(Coordinate c, Item i)
{
    /*if(isFree(c)){
        //if(this->isFree(c.getX + i.getWidth))
    }*/
    return false;
}
