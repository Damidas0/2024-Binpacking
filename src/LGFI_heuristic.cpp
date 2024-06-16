#include "LGFI_heuristic.h"
#include <iostream>
#include <list>
#include <algorithm> // for std::remove

LGFI_heuristic::LGFI_heuristic(const std::list<Item>& items, int bin_width, int bin_height)
    : items(items), bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
}

LGFI_heuristic::LGFI_heuristic(const std::vector<Item> &_items, int bin_width, int bin_height) 
    : bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
    items = std::list<Item>(_items.begin(), _items.end()); 
}

Solution LGFI_heuristic::solve()
{
    Solution solution;

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


        // // debug
        // std::cout << "\n--------------------------------\n";
        // std::cout << "Current position (" << current_fs->topLeft.getX() << ", " << current_fs->topLeft.getY() << ")\n";
        // std::cout << "Current fs dimensions: (" << current_fs->getWidth() << ", " << current_fs->getHeight() << ")\n";


        //gestion du perfect fit, si un item a exactement un dimension égale à la width du freespace teste de le placer

        for (auto it = this->items.begin(); it != this->items.end(); ++it)
        {
            Item item = *it;
            if (current_fs->getWidth() == item.getWidth() || current_fs->getWidth() == item.getHeight())
            {
                bool rotate = false;
                bool fit = current_fs->fitGlobal(item, rotate);
                if (fit)
                {
                    // std::cout << "Perfect fit\n";
                    if (rotate)
                    {   
                        //std::cout << "Rotating item\n";
                        item.rotate();
                    }
                    placeItemAndHandleFs(solution, item, it, itemPlacedFlag);
                    break;
                }
            }
        }

        if (!itemPlacedFlag) {

            // Pour current fs on essaie de rentrer chaque item
            for (auto it = this->items.begin(); it != this->items.end(); ++it)
            {


                Item item = *it;
                // std::cout << "Item " << item.m_id << " --> dimensions: (" << item.getWidth() << ", " << item.getHeight() << ")\n";

                // Si l'item rentre dans le freespace courant
                bool rotate = false;
                bool fit = current_fs->fitGlobal(item, rotate);

                // std::cout << "Fit: " << fit << " need to rotate: " << rotate << "\n";

                if (fit)
                {
                    // S'il faut le tourner on le fait
                    if (rotate) {
                        // std::cout << "Rotating item\n";
                        item.rotate();
                    }

                    // On place l'item dans le bin et on découpe le freespace
                    placeItemAndHandleFs(solution, item, it, itemPlacedFlag);

                    

                    break; // on passe à l'item suivant
                }
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

        }
    }

    return solution;
}

// Fonction encapsulant le placement de l'item et la gestion des free spaces
void LGFI_heuristic::placeItemAndHandleFs(Solution& solution, Item item, std::list<Item>::iterator it, bool& itemPlacedFlag)
{
                solution.listBin.front().add(item, current_fs->topLeft);
                // std::cout << "Item placed\n";

                // Maintenant le freespace est sous forme de L, on va le découper en 2 puis supprimer le freespace courant
                // On stock les données du freespace courant avant de supprimer

                int x = current_fs->topLeft.getX();
                int y = current_fs->topLeft.getY();
                int w = current_fs->getWidth();
                int h = current_fs->getHeight();

                // On supprime le freespace courant
                free_spaces.pop_front();

                //stratégie shorter left over 
                bool horizontal = (w-item.getWidth() < h-item.getHeight());

                if (horizontal)
                {
                    // std::cout << "Horizontal cut\n";
                    // Freespace en bas
                    if (h - item.getHeight() > 0) {
                        free_spaces.push_front(FreeSpace(w, h - item.getHeight(), Coordinate(x, y + item.getHeight())));
                        // std::cout << "Bottom free space added: (" << w << ", " << h - item.getHeight() << ") at (" << x << ", " << y + item.getHeight() << ")\n";
                    }
                    // Freespace à droite
                    if (w - item.getWidth() > 0) {
                        free_spaces.push_front(FreeSpace(w - item.getWidth(), item.getHeight(), Coordinate(x + item.getWidth(), y)));
                        // std::cout << "Right free space added: (" << w - item.getWidth() << ", " << item.getHeight() << ") at (" << x + item.getWidth() << ", " << y << ")\n";
                    }
                }
                else // coupe verticale
                {
                    // std::cout << "Vertical cut\n";
                    // Freespace en bas
                    if (h - item.getHeight() > 0) {
                        free_spaces.push_front(FreeSpace(item.getWidth(), h - item.getHeight(), Coordinate(x, y + item.getHeight())));
                        // std::cout << "Bottom free space added: (" << w << ", " << h - item.getHeight() << ") at (" << x << ", " << y + item.getHeight() << ")\n";
                    }
                    // Freespace à droite
                    if (w - item.getWidth() > 0) {
                        free_spaces.push_front(FreeSpace(w - item.getWidth(),h , Coordinate(x + item.getWidth(), y)));
                        // std::cout << "Right free space added: (" << w - item.getWidth() << ", " <<h<< ") at (" << x + item.getWidth() << ", " << y << ")\n";
                    }
                }
            

                // std::cout << "Number of freeSpaces in the list: " << free_spaces.size() << "\n";

                this->items.erase(it); // supprime directement l'élément sans utiliser std::remove
                itemPlacedFlag = true;
                //std::cout << "Item removed from the list, items remaining: " << this->items.size() << "\n";
                // solution.listBin.front().printIsFree();
}