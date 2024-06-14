#include "LGFI_heuristic.h"
#include <iostream>

LGFI_heuristic::LGFI_heuristic(std::list<Item> items, int bin_width, int bin_height)
    : items(items), bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
    this->free_spaces.push_back(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
    this->current_fs = &this->free_spaces.front(); // la bin en entier au début comme freespace
}

Solution LGFI_heuristic::solve()
{
    Solution solution;
    int n_bins = 1;

    // Ajout de la première bin
    solution.createNewBin(bin_width, bin_height);
    free_spaces.push_front(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));

    while (!this->items.empty()) // on répéte tant qu'il reste des items à placer
    {
        bool item_placed = false; // on initialise la variable qui indique si un item a été placé
        current_fs = &free_spaces.front(); // on prend le premier freespace de la liste (la liste doit rester ordonnée par ordre de lecture gauche à droite et de haut en bas)
        current_gap = current_fs->getWidth(); // on initialise la distance horizontale entre le curseur et le bord droit du bin
        current_position = current_fs->topLeft; // on initialise la position courante du curseu

        //debbug
        std::cout << std::endl; 
        std::cout << "--------------------------------" << std::endl;
        std::cout << "current position (" << current_position.getX() << ", " << current_position.getY() <<")" << std::endl;
        std::cout << "current gap : " << current_gap << std::endl;

        //pour ce freespace on test si le premier item de la liste peut y être placé sinon on passe à l'item suivant
        for (auto item : this->items)
        { 
            std::cout << std::endl << "item " << item.m_id << " : " << item.getWidth() << "x" << item.getHeight() << std::endl;
            if (this->current_gap >= item.getWidth() && item.getHeight() <= current_fs->getHeight()) //si il rentre sans rotation, on le place
            {
                solution.add(item, current_position, solution.listBin.front()); // on ajoute l'item à la solution dans la bin courante
                item_placed = true; // on indique qu'un item a été placé
                this->items.remove(item); // on retire l'item de la liste des items à placer (on ne le place qu'une fois)
                std::cout << "Item " << item.m_id<<" placed at " << current_position.getX() << ", " << current_position.getY() << std::endl;
                // on découpe le freespace en 2
                FreeSpace fs2 = FreeSpace(current_gap - item.getWidth(), current_fs->getHeight(), Coordinate(current_position.getX() + item.getWidth(), current_position.getX()));
                FreeSpace fs1 = FreeSpace(item.getWidth(), current_fs->getHeight() - item.getHeight(), Coordinate(current_position.getX(), current_position.getY() + item.getHeight()));
                // on retire le freespace courant de la liste
                free_spaces.pop_front();
                // on ajoute les 2 nouveaux freespace à la liste
                if (current_gap - item.getWidth() > 0) // si il reste de la place à droite de l'item
                {
                    free_spaces.push_front(fs1);
                }
                if (current_fs->getHeight() - item.getHeight() > 0) // si il reste de la place en dessous de l'item
                {
                    free_spaces.push_front(fs2);
                }
                break; // on sort de la boucle car on a placé un item
            }
        }

        // Si aucun item n'a été placé, on crée une nouvelle bin
        if (!item_placed)
        {
            solution.createNewBin(bin_width, bin_height);
            free_spaces.push_front(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
            n_bins++;
            std::cout << "bin " << n_bins << " created " << std::endl;
        }
    }

    return solution;
}

    
