#include "LGFI_heuristic.h"
#include <iostream>
#include <list>
#include <algorithm> // for std::remove

LGFI_heuristic::LGFI_heuristic(const std::list<Item>& items, int bin_width, int bin_height)
    : items(items), bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
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
        if (free_spaces.empty()) {
            std::cerr << "Error: No more free spaces available.\n";
            break;
        }

        bool itemPlacedFlag = false; // flag pour savoir si on a placé un item ou non
        current_fs = &free_spaces.front(); // on prend le premier freespace de la liste
        current_gap = current_fs->getWidth(); // on initialise la distance horizontale entre le curseur et le bord droit du bin
        current_position = current_fs->topLeft; // on initialise la position courante du curseur

        // Pour current fs on essaie de rentrer chaque item
        for (auto it = this->items.begin(); it != this->items.end(); ++it)
        {
            // debug
            std::cout << "\n--------------------------------\n";
            std::cout << "Current position (" << current_fs->topLeft.getX() << ", " << current_fs->topLeft.getY() << ")\n";
            std::cout << "Current fs dimensions: (" << current_fs->getWidth() << ", " << current_fs->getHeight() << ")\n";

            Item item = *it;
            std::cout << "Item " << item.m_id << " --> dimensions: (" << item.getWidth() << ", " << item.getHeight() << ")\n";

            // Si l'item rentre dans le freespace courant
            bool rotate = false;
            bool fit = true; ///current_fs->fitGlobal(current_fs->topLeft, item, rotate);

            std::cout << "Fit: " << fit << " need to rotate: " << rotate << "\n";

            if (fit)
            {
                // S'il faut le tourner on le fait
                if (rotate) {
                    item.rotate();
                }

                solution.listBin.front().add(item, current_fs->topLeft);
                std::cout << "Item placed\n";

                // Maintenant le freespace est sous forme de L, on va le découper en 2 puis supprimer le freespace courant
                // On stock les données du freespace courant avant de supprimer

                int x = current_fs->topLeft.getX();
                int y = current_fs->topLeft.getY();
                int w = current_fs->getWidth();
                int h = current_fs->getHeight();

                // On supprime le freespace courant
                free_spaces.pop_front();

                // On teste si on peut ajouter des freespace à gauche et en bas de l'item
                // Pour l'instant on coupe toujours horizontalement
                // Freespace en bas
                if (h - item.getHeight() > 0) {
                    free_spaces.push_front(FreeSpace(w, h - item.getHeight(), Coordinate(x, y + item.getHeight())));
                    std::cout << "Bottom free space added: (" << w << ", " << h - item.getHeight() << ") at (" << x << ", " << y + item.getHeight() << ")\n";
                }
                // Freespace à droite
                if (w - item.getWidth() > 0) {
                    free_spaces.push_front(FreeSpace(w - item.getWidth(), item.getHeight(), Coordinate(x + item.getWidth(), y)));
                    std::cout << "Right free space added: (" << w - item.getWidth() << ", " << item.getHeight() << ") at (" << x + item.getWidth() << ", " << y << ")\n";
                }

                std::cout << "Number of freeSpaces in the list: " << free_spaces.size() << "\n";

                this->items.erase(it); // supprime directement l'élément sans utiliser std::remove
                itemPlacedFlag = true;
                std::cout << "Item removed from the list, items remaining: " << this->items.size() << "\n";
                solution.listBin.front().printIsFree();

                break; // on passe à l'item suivant
            }
        }

        // Si aucun objet n'a été placé dans le freespace courant on le supprime
        if (!itemPlacedFlag)
        {
            free_spaces.pop_front();
        }

        if (free_spaces.empty() && !this->items.empty()) // si on a vidé la liste des freespace et qu'il reste des items
        {
            solution.createNewBin(bin_width, bin_height);
            free_spaces.push_front(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
            n_bins++;
        }
    }

    return solution;
}
