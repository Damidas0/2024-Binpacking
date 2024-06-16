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

    /**
     * @brief stocke les valeurs de fitness des solutions trouvées (toutes les 10 itérations) pour tracer la courbe
     */
    std::vector<float> fitness_values;


    /**
     * @brief Fonction qui initialise les paramètres de l'algorithme et qui permet de changer d'énoncé sans recréer l'objet
     * @warning il faut avoir change l'énoncé avant d'appeler cette fonction
     */
    void initialize();


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

    /**
     * @brief Fonction qui dump en json les valeurs de fitness
     */
    void DumpFitnessValues(std::string file_path);

    /**
     * @brief Fonction qui met à jour l'énoncé et réinitialise les paramètres de l'algorithme en fonction de ce nouvel énoncé. 
     */
    void updateEnnonce(Ennonce enonce) override; 

};

#endif // TABOUSEARCH_H
