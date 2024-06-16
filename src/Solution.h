#pragma once
#include<list>
#include"Item.h"
#include"JsonWriter.h"
#include <unordered_map>
#include <map>
 
#include"Bin.h"


class Solution
{
private:
   
    /**
     * @brief map qui associe un item à un bin
     */
    //std::unordered_map<Item, Bin*> map; 

    /**
     * @brief Fonction qui teste si un item peut être placé dans un bin à une certaine coordonnée en utilisant la fonction fit de Bin
     */
    //bool fit(Item i, Coordinate c, Bin b);

public:
    /**
     * @brief Constructeur de la classe Solution qui fait pas grand chose pour l'instant
     */
    Solution();
    /**
     * @brief Destructeur de la classe Solution qui fait pas grand chose pour l'instant
     */
    ~Solution();
    /**
     * @brief Nombre de bins
     */
    int nbBins;

    /**
     * @brief Fonction qui évalue la solution en sommant le nombre de places libres dans chaque bin + le remplissage de la dernière bin
     */
    float Fitness() const;
    

    /**
     * @brief Fonction qui sérialise la solution dans un fichier de sortie
     */
    void dumpToJson(const std::string& file_path) const;

    //fct emplacement valide
    //fct place qui fait appel à fit de bin
    /**
     * @brief Fonction qui place un item dans un bin à une certaine coordonnée
     * @param i item à placer
     * @param c coordonnée de la case en haut à gauche de l'item
     * @param b bin dans lequel on veut placer l'item (fait partie de la liste de bins de la solution)
     * @par Cette fonction appelle la fonction fit de Bin pour tester si l'item peut être placé à la coordonnée donnée et le place si c'est le cas en mettant à jour la map et la liste is_free du bin
     */
    void add(Item i, Coordinate c, Bin& b);
    
    /**
     * @brief Fonction qui crée un nouveau bin avec les dimensions données (comme ça sera la classe Algo qui stocke l'énoncé on passe les dimensions en paramètre)
     * @param width largeur du bin
     * @param height hauteur du bin
     * @par Cette fonction crée un nouveau bin avec les dimensions données et l'ajoute à la liste de bins de la solution
     */
    void createNewBin(int width, int height); 

    //renvoi liste coint hg 

    //l'ordre de prio est hauteur puis "gaucheur"

    //membres: 

    /**
     * @brief list des bins de la solution
     */
    std::list<Bin> listBin;
    

};
