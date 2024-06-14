#include "LGFI_heuristic.h"
#include <iostream>
#include <list>

LGFI_heuristic::LGFI_heuristic(const std::list<Item>& items, int bin_width, int bin_height)
    : items(items), bin_width(bin_width), bin_height(bin_height), current_gap(bin_width), current_position(0, 0)
{
    // this->free_spaces.push_back(FreeSpace(bin_width, bin_height, Coordinate(0, 0)));
    // this->current_fs = &this->free_spaces.front(); // la bin en entier au début comme freespace
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
        current_fs = &free_spaces.front(); // on prend le premier freespace de la liste (la liste doit rester ordonnée par ordre de lecture gauche à droite et de haut en bas)
        current_gap = current_fs->getWidth(); // on initialise la distance horizontale entre le curseur et le bord droit du bin
        current_position = current_fs->topLeft; // on initialise la position courante du curseur

        //debug
        std::cout << std::endl; 
        std::cout << "--------------------------------" << std::endl;
        std::cout << "current position (" << current_position.getX() << ", " << current_position.getY() <<")" << std::endl;
        std::cout << "current fs dimensions : (" << current_fs->getWidth() << ", " << current_fs->getHeight() << ")" << std::endl;

        //Pour current fs on essaie de rentrer chaque item
        for (auto it = this->items.begin(); it != this->items.end(); ++it)
        {


            //debug
            std::cout << std::endl; 
            std::cout << "--------------------------------" << std::endl;
            std::cout << "current position (" << current_fs->topLeft.getX() << ", " << current_fs->topLeft.getY() <<")" << std::endl;
            std::cout << "current fs dimensions : (" << current_fs->getWidth() << ", " << current_fs->getHeight() << ")" << std::endl;


            Item item = *it;
            std::cout << "item " << item.m_id << " --> dimensions : (" << item.getWidth() << ", " << item.getHeight() << ")" << std::endl;

            //si l'item rentre dans le freespace courant
            bool rotate = false;
            bool fit = current_fs->fitGlobal(current_fs->topLeft, item, rotate);

            std::cout << "fit : " << fit << " need to rotate : " << rotate << std::endl;

            if (fit)
            {
                //s'il faut le tourner on le fait
                if (rotate)
                {
                    item.rotate();
                }

                //on ajoute l'item à la solution
                solution.add(item, current_fs->topLeft, solution.listBin.back());
                std::cout << "item placed" << std::endl;

                //maintenant le freespace est sous forme de L, on va le découper en 2 puis supprimer le freespace courant
                //on stock les donnée du freespace courant avant de supprimer

                int x = current_fs->topLeft.getX();
                int y = current_fs->topLeft.getY();
                int w = current_fs->getWidth();
                int h = current_fs->getHeight();

                //on supprime le freespace courant
                free_spaces.pop_front();

                //on test si on peut ajouter des freespace à gauche et en bas de l'item
                //pour l'instant on coupe toujours horizontalement
                //freespace en bas
                if(h-item.getHeight() > 0)
                {
                    free_spaces.push_front(FreeSpace(w, h-item.getHeight(), Coordinate(x, y+item.getHeight())));
                    std::cout << "bottom free space added : (" << w << ", " << h-item.getHeight() << ") at (" << x << ", " << y+item.getHeight() << ")" << std::endl;
                }
                //freespace à droite
                if (w-item.getWidth() > 0)
                {
                    free_spaces.push_front(FreeSpace(w-item.getWidth(), item.getHeight(), Coordinate(x+item.getWidth(), item.getHeight())));
                    std::cout << "right free space added : (" << w-item.getWidth() << ", " << item.getHeight() << ") at (" << x+item.getWidth() << ", " << item.getHeight() << ")" << std::endl;
        
                }

                std::cout << "nb of freeSpace in the list : " << free_spaces.size() << std::endl;
                std::cout << "--------------------------------" << std::endl;

            

                //on supprime l'item de la liste
                this->items.erase(it);
                break; //on sort de la boucle for


            }




        }
    }

    return solution;

}


