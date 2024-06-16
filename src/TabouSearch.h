#ifndef TABOUSEARCH_H
#define TABOUSEARCH_H

#include <iostream>
#include "Solution.h"
#include "LGFI_heuristic.h"
#include "AlgoAbstract.h"
#include "Ennonce.h"
#include <list>
#include <deque>
#include "Item.h"

class TabouSearch : public AlgoAbstract
{
private:
    /**
     * @brief Génère tous les voisins de la solution courante
     * @details On fait une rotation d'un élément
     * @return std::list<std::list<Item>> 
     */
    std::list<std::list<Item>> generateAllNeighbors();

    /**
     * @brief La liste tabou pour stocker les mouvements interdits
     */
    std::deque<std::list<Item>> tabouList;

    /**
     * @brief La taille maximale de la liste tabou
     */
    int tabouListMaxSize;

    /**
     * @brief Vérifie si une solution est dans la liste tabou
     */
    bool isTabou(const std::list<Item>& solution);

public:
    /**
     * @brief Constructeur de la classe TabouSearch
     */
    TabouSearch(Ennonce enonce);  

    /**
     * @brief Constructeur par défaut de la classe TabouSearch
     */
    TabouSearch(); 

    /**
     * @brief La solution en cours
     */
    Solution Current;

    /**
     * @brief La meilleure solution trouvée
     */
    Solution BestSolution;

    /**
     * @brief La liste d'items qui représente la solution courante
     */
    std::list<Item> CurrentList;

    /**
     * @brief Fonction qui lance l'algorithme
     */
    void run() override;
};

#endif // TABOUSEARCH_H
