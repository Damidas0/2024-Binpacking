#ifndef BIN_H
#define BIN_H


#include "Rectangle.h"
#include<list>
#include "Item.h"
#include"JsonWriter.h"
#include "Ennonce.h"

#include <ostream>

class Bin : public Rectangle{
    private:

        
    public:
        /**
         * @brief Liste des items dans le bin
         */
        std::list<Item> items;
        
        
    public:

    
        /**
         * @brief Constructeur de la classe Bin qui initialise la grille is_free et crée les bins avec les bonnes dimensions 
         */
        Bin(int width, int height);
        /**
         * @brief Fonction qui sérialise le bin dans un fichier de sortie
         */
        void serialize(std::ofstream& outputFile) const;

        void addItem(Item i);
        

        /**
         * @brief Fonction qui renvoi le nombre de place libre dans le bin
         */
        int freeSpace() const; //renvoi la place totale restante libre
        /**
         * @brief Grille (vector 2D booleen) qui indique si chaque case est occupée ou non
         * @warning bien penser à mettre à jour cette grille à chaque ajout d'item
         * @remark width x height (pas l'inverse)
         */
        std::vector<std::vector<bool>> is_free; 
        /**
         * @brief Fonction qui renvoi si une case est libre ou non
         * @param c coordonnée de la case à tester
         * @return true si la case est libre, false sinon
         */
        bool fit(Coordinate c, Item i);
        bool fitRotate(Coordinate c, Item i);
        /**
         * @brief Fonction qui teste si un item peut être placé dans le bin à une certaine coordonnée peu importe la rotation 
         * @param rotate booléen qui indique si l'item doit être tourné ou non qui est passé par référence et qui est modifié par la fonction
         */
        bool fitGlobal(Coordinate c, Item i, bool& rotate); 


  

        /**
         * @brief fonction qui affiche la grille is_free
         */
        void printIsFree() const;
       
         

};

#endif