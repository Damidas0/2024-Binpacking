#include "Testing.h"
#include "AlgoNaive.h"
#include "Ennonce.h"
#include "Solution.h"
#include <fstream>
#include <iostream>
#include <chrono>


void Testing::dumpSolutionAllInstances(AlgoAbstract& algo, const std::string& file_path)
{
    float resultFitnes[13];
    std::string instances[] = {
        "data/binpacking2d/binpacking2d-01.bp2d",
        "data/binpacking2d/binpacking2d-02.bp2d",
        "data/binpacking2d/binpacking2d-03.bp2d",
        "data/binpacking2d/binpacking2d-04.bp2d",
        "data/binpacking2d/binpacking2d-05.bp2d",
        "data/binpacking2d/binpacking2d-06.bp2d",
        "data/binpacking2d/binpacking2d-07.bp2d",
        "data/binpacking2d/binpacking2d-08.bp2d",
        "data/binpacking2d/binpacking2d-09.bp2d",
        "data/binpacking2d/binpacking2d-10.bp2d",
        "data/binpacking2d/binpacking2d-11.bp2d",
        "data/binpacking2d/binpacking2d-12.bp2d",
        "data/binpacking2d/binpacking2d-13.bp2d"
    }; 

    //mesure du temps
    float ExeTime[13];
    

    for (int i = 0; i < 13; ++i)
    {
        Ennonce m(instances[i]);
        algo.updateEnnonce(m);
        auto start = std::chrono::high_resolution_clock::now();
        algo.run();
        resultFitnes[i] = algo.m_solution.Fitness();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        ExeTime[i] = duration.count();
    }
    
    
    // Création du fichier de sortie
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << file_path << std::endl;
        return;
    }

    // Début du format JSON
    file << "{\n";
    file << "  \"instances\": [\n";

    // Écriture des résultats pour chaque instance
    for (int i = 0; i < 13; ++i)
    {
        file << "    {\n";
        file << "      \"instance\": \"" << i+1 << "\",\n";
        file << "      \"fitness\": " << resultFitnes[i] << ",\n";
        file << "      \"execution_time\": " << ExeTime[i] << "\n";
        file << "    }";
        if (i < 12) {
            file << ",";
        }
        file << "\n";
    }

    // Fin du format JSON
    file << "  ]\n";
    file << "}\n";

    // Fermeture du fichier
    file.close();
}
