#include "Coordinate.h"
#include <list>
#include "Item.h"
#include "FreeSpace.h"
#include "Solution.h"
/**
 * @brief classe qui a pour but de prendre en entrée une liste ordonnée d'items et de retourner une solution
 */
class LGFI_heuristic
{
private:
    /* data */
public:
    /**
     * @brief Constructeur de la classe LGFi_heuristic qui prend en entrée une liste ordonnée d'items et les dimensions du bin
     */
    LGFI_heuristic(const std::list<Item>& items, int bin_width, int bin_height);

    /**
     * renvoie une solution
     */
    Solution solve();

    



    //attributs
    /**
     * @pointeur sur le freespace courant
     */
    FreeSpace* current_fs;
    
    /**
     * @brief Liste ordonnée des items à placer
     */
    std::list<Item> items;
    /**
     * @brief Largeur du bin
     */
    int bin_width;
    /**
     * @brief Hauteur du bin
     */
    int bin_height;
    
    /**
     * @brief Liste des espaces rectangulaires libres dans le bin
     */
    std::list<FreeSpace> free_spaces;

    /**
     * @brief Espace libre (rectangle) courant
     */
    //FreeSpace current_fs;
   
    /**
     * @brief Distance horizontale entre le curseur et le bord droit du bin
     */
    int current_gap;

    /**
     * @brief Position courante du curseur
     */
    Coordinate current_position;






    
};


