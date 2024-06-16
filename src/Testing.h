#include <iostream>
#include "AlgoAbstract.h"
#include <string> // Correction de l'inclusion de la bibliothèque


/**
 * @class pour tester un algo sur tout les exemples de l'énoncé et dump les résultats en json et eventuemment tester d'autres trucs
 */
class Testing
{
    public: 
        /**
         * @brief Fonction qui dump les résultats de l'algo sur toutes les instances de l'énoncé
         * @param algo l'algo à tester
         * @param file_path le chemin du fichier de sortie
         */
        void dumpSolutionAllInstances(AlgoAbstract& algo, const std::string& file_path);
}; 