#include "Bin.h" 
#include "Coordinate.h"





Bin::Bin(int width, int height)
    : Rectangle(width, height) {}

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

// Fonction potentiellemnt optimisable
std::vector<Coordinate> Bin::listFreeCoordinates() const { 
    int width = this->getWidth();
    int height = this->getHeight();
    
    //liste toutes les coordonnées libre pour lesquel il existe aucune autre coordonnée libre qui est plus en haut ET plus à gauche
    std::vector<Coordinate> dominant_free_coordinates;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (this->is_free[y][x]) {
                if(dominant_free_coordinates.empty()){
                    dominant_free_coordinates.push_back(Coordinate(x, y));
                }

                else
                {
                    bool is_dominant = false; 
                    for (auto it = dominant_free_coordinates.begin(); it != dominant_free_coordinates.end(); ++it)
                    {
                        if (x < it->getX() && y < it->getY())
                        {
                            is_dominant = true;
                            it = dominant_free_coordinates.erase(it);
                        }
                    }
                    if (is_dominant)
                    {
                        dominant_free_coordinates.push_back(Coordinate(x, y));
                    }
                }
               
            }
        }
    }

    return dominant_free_coordinates;


}
