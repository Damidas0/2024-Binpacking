#include "TabouSearch.h"
#include <random>  

TabouSearch::TabouSearch(Ennonce enonce) : AlgoAbstract(enonce)
{
    CurrentList = m_enonce.items;
    int bin_width = m_enonce.bin_width;
    int bin_height = m_enonce.bin_height;

    // On part de la solution de l'algo naïf, c'est-à-dire de LGFI avec une liste triée
    this->CurrentList.sort([](Item a, Item b) { return a.getArea() > b.getArea(); });

    // On initialise LGFI
    LGFI_heuristic lgfi(this->CurrentList, bin_width, bin_height);
    
    this->m_solution = lgfi.solve();
    this->Current = this->m_solution;
    this->BestSolution = this->m_solution;

    tabouListMaxSize = 10; 
}

std::list<std::list<Item>> TabouSearch::generateAllNeighbors() {
    std::list<std::list<Item>> allNeighbors;
    
    // Rotate un item aléatoire
    for (auto it = CurrentList.begin(); it != CurrentList.end(); ++it) {
        std::list<Item> neighbor = CurrentList; 
        auto itNeighbor = neighbor.begin();
        std::advance(itNeighbor, std::distance(CurrentList.begin(), it));
        itNeighbor->rotate(); 
        allNeighbors.push_back(neighbor);
    }


    // swap deux items cote à cote
    for (auto it = CurrentList.begin(); it != CurrentList.end(); ++it) {
        auto nextIt = std::next(it);
        if (nextIt != CurrentList.end()) {
            std::list<Item> neighbor = CurrentList;
            auto itNeighbor1 = neighbor.begin();
            std::advance(itNeighbor1, std::distance(CurrentList.begin(), it));
            auto itNeighbor2 = std::next(itNeighbor1);
            std::swap(*itNeighbor1, *itNeighbor2);
            allNeighbors.push_back(neighbor);
        }
    }

    return allNeighbors;
}

bool TabouSearch::isTabou(const std::list<Item>& solution) {
    for (const auto& tabouSolution : tabouList) {
        if (tabouSolution == solution) {
            return true;
        }
    }
    return false;
}

void TabouSearch::run()
{   

    int compteur = 0;
    std::cout << "Fitness de la solution initiale: " << Current.Fitness() << std::endl;

    while (compteur < 50) // Arrêt après un certain nombre d'itérations
    {   
        std::list<std::list<Item>> allNeighbors = generateAllNeighbors();
        std::list<Item> bestNeighbor;
        Solution bestNeighborSolution;
        double bestNeighborFitness = std::numeric_limits<double>::max();

        for (const auto& neighbor : allNeighbors) {
            if (!isTabou(neighbor)) {
                LGFI_heuristic lgfi(neighbor, m_enonce.bin_width, m_enonce.bin_height);
                Solution neighborSolution = lgfi.solve(); // Solution de LGFI avec la liste neighbor
                double neighborFitness = neighborSolution.Fitness(); // Fitness de la solution de LGFI avec la liste neighbor

                if (neighborFitness < bestNeighborFitness) {
                    bestNeighbor = neighbor;
                    bestNeighborSolution = neighborSolution;
                    bestNeighborFitness = neighborFitness;
                }
            }
        }

        if (bestNeighborFitness < Current.Fitness()) {
            CurrentList = bestNeighbor;
            Current = bestNeighborSolution;

            if (BestSolution.Fitness() > bestNeighborFitness) {
                BestSolution = bestNeighborSolution;
                std::cout << "Nouvelle meilleure solution trouvée" << std::endl;
            }
        }
        // Ajouter la solution courante à la liste tabou
        tabouList.push_back(bestNeighbor);
        if (tabouList.size() > tabouListMaxSize) {
            tabouList.pop_front();
        }

        compteur++;
        if (compteur % 5 == 0) {
            std::cout << "------------Iteration: " << compteur << "----------------" << std::endl;
            std::cout << "Current fitness: " << Current.Fitness() << std::endl;
            std::cout << "Best fitness: " << BestSolution.Fitness() << std::endl;

        }
    }

    m_solution = BestSolution;
    m_solution.dumpToJson("output.json");
    std::cout << "Solution dumped to output.json" << std::endl;
}
