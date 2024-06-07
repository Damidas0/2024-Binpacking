#include "Bin.h" 
#include "Coordinate.h"





Bin::Bin(int width, int height)
    : Rectangle(width, height) {}

int Bin::freeSpace() const {
    int bin_space_total = this->getArea(); // aire totale de la bin
    int bin_space_used = 0; // on fait la sommes des aires des items de la bin
    for(auto item : this->items){
        bin_space_used += item.getArea();
    }

    return bin_space_total - bin_space_used;

}

bool Bin::isFree(Coordinate c) {
    for(auto item : this->items)
    {
        Coordinate vertex1 = item.topLeft;
        Coordinate vertex4 = Coordinate(vertex1.getX() + item.getWidth(), vertex1.getY() + item.getHeight()); // sommet en bas à droite

        if (c.getX() >= vertex1.getX() && c.getX() <= vertex4.getX() && c.getY() >= vertex1.getY() && c.getY() <= vertex4.getY())
        {
            return false;
        }


    }
    return true;

}

// std::list<Coordinate> Bin::listFreeCoordinates() const {
//     //liste toutes les coordonnées libre pour lesquel il existe aucune autre coordonnée libre qui est plus en haut ET plus à gauche
//     std::list<Coordinate> free_coordinates; 
//     int width = this->getWidth();
//     int height = this->getHeight();
    
//     // Création de la grille de disponibilité
//     std::vector<std::vector<bool>> is_free(height, std::vector<bool>(width, true));
    
//     // Marquer les cellules occupées par les items
//     for (auto item : this->items) {
//         Coordinate topLeft = item.topLeft;
//         for (int y = topLeft.getY(); y < topLeft.getY() + item.getHeight(); ++y) {
//             for (int x = topLeft.getX(); x < topLeft.getX() + item.getWidth(); ++x) {
//                 is_free[y][x] = false;
//             }
//         }
//     }

//     // Parcourir la grille pour trouver les coordonnées libres dominantes
//     std::list<Coordinate> dominants_free_coordinates;
//     for (int y = 0; y < height; ++y) {
//         for (int x = 0; x < width; ++x) {
//             if (is_free[y][x]) {
//                 bool is_dominant = true;

//                 // Vérifier si la coordonnée est dominante en la comparant avec les coordnnée dominantes actuelles
//                 }

          
//         }
//     }




// }
