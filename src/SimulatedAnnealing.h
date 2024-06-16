#include <iostream>
#include "Solution.h"
#include "LGFI_heuristic.h"
#include "AlgoAbstract.h"
#include "Ennonce.h"
#include <list>
#include "Item.h"

class SimulatedAnnealing: public AlgoAbstract
{
private:
    /**
     * @brief Génère un voisin de la solution courante
     * @details On choisit deux items aléatoirement et on les échange
     * @return std::list<Item> 
     */
    std::list<Item> generateNeighbor();



    
    



public:
    /**
     * @brief Constructeur de la classe SimulatedAnnealing
     */
    SimulatedAnnealing(Ennonce enonce);  
    /**
     * @brief Constructeur par défault de la classe SimulatedAnnealing
     */
    SimulatedAnnealing(); 
    /**
     * @brief La solution en cours
     */
    Solution Current;
    // on stocke la meilleure solution trouvée dans m_solution herité de AlgoAbstract
    /**
     * @temperature
     */
    double temperature;

    /**
     * @brief list d'item qui représente la solution courante
     */
    std::list<Item> CurrentList;

    /**
     * @brief facteur de décroissance de la température
     */
    float lambda;

    /**
     * @brief Fonction qui lance l'algorithme
     */
    void run() override;


};

