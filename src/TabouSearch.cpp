#include "TabouSearch.h"
#include <random>  
#include <fstream>
#include <algorithm>

TabouSearch::TabouSearch(Ennonce enonce) : AlgoAbstract(enonce)
{
    initialize();
}

void TabouSearch::initialize()
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

    tabouListMaxSize = 100; 
}

void TabouSearch::updateEnnonce(Ennonce enonce)
{
    m_enonce = enonce;
    initialize();
}

void TabouSearch::DumpFitnessValues(std::string file_path)
{
    std::ofstream outputFile(file_path);
    if (outputFile.is_open()) {
        outputFile << "{\n";
        outputFile << "    \"fitness_values\": [\n";
        bool firstValue = true;
        for (const auto& value : fitness_values) {
            if (!firstValue) {
                outputFile << ",\n";
            }
            outputFile << "        " << value;
            firstValue = false;
        }
        outputFile << "\n    ]\n";
        outputFile << "}\n";
        outputFile.close();

        std::cout << "JSON file has been saved\n";
    } else {
        std::cerr << "Unable to open the file for writing JSON dump.\n";
    }
}

std::list<std::list<Item>> TabouSearch::generateAllNeighbors() {
    std::list<std::list<Item>> allNeighbors;
    
    // Rotate un item
    for (auto it = CurrentList.begin(); it != CurrentList.end(); ++it) {
        std::list<Item> neighbor = CurrentList; 
        auto itNeighbor = neighbor.begin();
        std::advance(itNeighbor, std::distance(CurrentList.begin(), it));
        itNeighbor->rotate(); 
        allNeighbors.push_back(neighbor);
    }

    // Swap deux items contigus
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

    // Supprimer un élément et le réinsérer à une position aléatoire
    for (auto it = CurrentList.begin(); it != CurrentList.end(); ++it) {
        std::list<Item> neighbor = CurrentList;
        auto itNeighbor = neighbor.begin();
        std::advance(itNeighbor, std::distance(CurrentList.begin(), it));
        Item item = *itNeighbor;
        neighbor.erase(itNeighbor);

        // Générer une position aléatoire pour la réinsertion
        auto insertPos = neighbor.begin();
        std::advance(insertPos, rand() % (neighbor.size() + 1));
        neighbor.insert(insertPos, item);

        allNeighbors.push_back(neighbor);
    }

    return allNeighbors;
}

bool TabouSearch::isTabou(const std::list<Item>& solution) {
    return std::find(tabouList.begin(), tabouList.end(), solution) != tabouList.end();
}

void TabouSearch::run()
{   
    int compteur = 0;
    int noImprovementCount = 0;
    const int maxNoImprovement = 25; // Arrêt après un certain nombre d'itérations sans amélioration

    std::cout << "Fitness de la solution initiale: " << Current.Fitness() << std::endl;

    while (compteur < 100 && noImprovementCount < maxNoImprovement) // Arrêt après un certain nombre d'itérations ou sans amélioration
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
                noImprovementCount = 0; // Réinitialiser le compteur de non-amélioration
            } else {
                noImprovementCount++;
            }
        } else {
            noImprovementCount++;
        }

        // Ajouter la solution courante à la liste tabou
        tabouList.push_back(bestNeighbor);
        if (tabouList.size() > tabouListMaxSize) {
            tabouList.pop_front();
        }

        compteur++;
        if (compteur % 2 == 0) //toutes les 2 itérations on stocke la fitness
        {
            fitness_values.push_back(Current.Fitness());
        }
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
