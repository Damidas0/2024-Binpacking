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


//fonction potentiellement optimisable
std::list<Coordinate> Bin::listFreeCoordinates() const { 
    int width = this->getWidth();
    int height = this->getHeight();
    
    // Liste toutes les coordonnées libres pour lesquelles il n'existe aucune autre coordonnée libre qui est plus en haut ET plus à gauche
    std::list<Coordinate> dominant_free_coordinates;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (this->is_free[y][x]) {
                if(dominant_free_coordinates.empty()){
                    dominant_free_coordinates.push_back(Coordinate(x, y));
                } else {
                    bool is_dominant = false; 
                    for (auto it = dominant_free_coordinates.begin(); it != dominant_free_coordinates.end();) {
                        if (x < it->getX() && y < it->getY()) {
                            is_dominant = true;
                            it = dominant_free_coordinates.erase(it);
                        } else {
                            ++it;
                        }
                    }
                    if (is_dominant) {
                        dominant_free_coordinates.push_back(Coordinate(x, y));
                    }
                }
            }
        }
    }

    return dominant_free_coordinates;
}
