#include <iostream>
#include "Solution.h"
#include "LGFI_heuristic.h"
#include "AlgoAbstract.h"
#include "Ennonce.h"
#include <list>
#include "Item.h"
#include <fstream>

class SimulatedAnnealing: public AlgoAbstract
{
private:
    /**
     * @brief Génère un voisin de la solution courante
     * @details On choisit deux items aléatoirement et on les échange
     * @return std::list<Item> 
     */
    std::list<Item> generateNeighbor();

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
     * @brief Nombre d'itérations
     */
    int iterations;

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

    /**
     * @brief Fonction qui dump en json les valeurs de fitness
     */
    void DumpFitnessValues(std::string file_path);
    /**
     * @brief Fonction qui met à jour l'énoncé et réinitialise les paramètres de l'algorithme en fonction de ce nouvel énoncé. 
     */
    void updateEnnonce(Ennonce enonce) override; 



};

