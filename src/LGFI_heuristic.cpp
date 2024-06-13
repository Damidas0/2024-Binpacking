#include "LGFI_heuristic.h"
#include <iostream>

LGFI_heuristic::LGFI_heuristic(std::list<Item> items, int bin_width, int bin_height)
    : items(items), bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
    this->free_spaces.push_back(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
    this->current_fs = &this->free_spaces.front(); // la bin en entier au début comme freespace
}

// Solution LGFI_heuristic::solve()
// {
//     Solution solution;
//     int n_bins = 1;

//     while (!this->items.empty()) // on répéte tant qu'il reste des items à placer
//     {
        
        
//         bool item_placed = false; // on initialise la variable qui indique si un item a été placé
//         current_fs = &free_spaces.front(); // on prend le premier freespace de la liste (la liste doit rester ordonnée par ordre de lecture gauche à droite et de haut en bas)
//         free_spaces.pop_front(); // on le retire de la liste (dans tous les cas il sera remplacé par 2 freespace ou aucun si aucun item ne rentre )
//         current_gap = current_fs->getWidth(); // on initialise la distance horizontale entre le curseur et le bord droit du bin
//         current_position = current_fs->topLeft; // on initialise la position courante du curseur

//         //pour ce freespace on test si le premier item de la liste peut y être placé sinon on passe à l'item suivant
//         for (auto item : this->items)
//         {
//             if (this->current_gap >= item.getWidth() && item.getHeight() <= current_fs->getHeight()) //si il rentre sans rotation, on le place
//             {
//                 solution.add(item, current_position, solution.listBin.front()); // on ajoute l'item à la solution dans la bin courante
//                 item_placed = true; // on indique qu'un item a été placé
//                 this->items.remove(item); // on retire l'item de la liste
//                 std::cout << "Item placed at " << current_position.getX() << ", " << current_position.getY() << std::endl;
//                 // on découpe le freespace en 2
//                 if (current_gap - item.getWidth() > 0) // si il reste de la place à droite de l'item #TODO gérer les stratégie pour l'instant on coupe toujours horizontalement
//                 {
//                     free_spaces.push_front(FreeSpace(current_gap - item.getWidth(), current_fs->getHeight(), Coordinate(current_position.getX() + item.getWidth(), current_position.getX())));
//                     free_spaces.push_front(FreeSpace(item.getWidth(), current_fs->getHeight() - item.getHeight(), Coordinate(current_position.getX(), current_position.getY() + item.getHeight())));
//                 }
//                 // #TODO gérer le cas de la rotation
//                 // #TODO gérer le cas du merge de freespace
//                 break; // on sort de la boucle car on a placé un item
//             }
//         }

//         //on teste si la liste de freespace est vide, si c'est le cas on crée une nouvelle bin et on ajoute le premier freespace
//         if (free_spaces.empty())
//         {
//             solution.createNewBin(bin_width, bin_height);
//             free_spaces.push_front(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
//             std::cout << ++n_bins << " bins created" << std::endl;
//         }

//     }




Solution LGFI_heuristic::solve()
{
    Solution solution;
    int n_bins = 1;

    while (!this->items.empty()) // on répète tant qu'il reste des items à placer
    {
        bool item_placed = false; // on initialise la variable qui indique si un item a été placé
        current_fs = &free_spaces.front(); // on prend le premier freespace de la liste (la liste doit rester ordonnée par ordre de lecture gauche à droite et de haut en bas)
        free_spaces.pop_front(); // on le retire de la liste (dans tous les cas il sera remplacé par 2 freespace ou aucun si aucun item ne rentre)
        current_gap = current_fs->getWidth(); // on initialise la distance horizontale entre le curseur et le bord droit du bin
        current_position = current_fs->topLeft; // on initialise la position courante du curseur

        // pour ce freespace, on teste si le premier item de la liste peut y être placé sinon on passe à l'item suivant
        for (auto it = this->items.begin(); it != this->items.end(); ++it)
        {
            Item item = *it;
            if (this->current_gap >= item.getWidth() && item.getHeight() <= current_fs->getHeight()) // s'il rentre sans rotation, on le place
            {
                solution.add(item, current_position, solution.listBin.front()); // on ajoute l'item à la solution dans la bin courante
                item_placed = true; // on indique qu'un item a été placé
                this->items.erase(it); // on supprime l'item de la liste

                // on découpe le freespace en 2
                if (current_gap - item.getWidth() > 0) // s'il reste de la place à droite de l'item #TODO gérer les stratégies pour l'instant on coupe toujours horizontalement
                {
                    free_spaces.push_front(FreeSpace(current_gap - item.getWidth(), current_fs->getHeight(), Coordinate(current_position.getX() + item.getWidth(), current_position.getY())));
                }
                if (current_fs->getHeight() - item.getHeight() > 0) // s'il reste de la place en dessous de l'item
                {
                    free_spaces.push_front(FreeSpace(item.getWidth(), current_fs->getHeight() - item.getHeight(), Coordinate(current_position.getX(), current_position.getY() + item.getHeight())));
                }
                // #TODO gérer le cas de la rotation
                // #TODO gérer le cas du merge de freespace
                break; // on sort de la boucle car on a placé un item
            }
        }

        // on teste si la liste de freespace est vide, si c'est le cas on crée une nouvelle bin et on ajoute le premier freespace
        if (free_spaces.empty())
        {
            solution.createNewBin(bin_width, bin_height);
            free_spaces.push_front(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
            std::cout << ++n_bins << " bins created" << std::endl;
        }
    }

    return solution;
}    


    
