#pragma once

#include "AlgoAbstract.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "Ennonce.h"
#include "LGFI_heuristic.h"
#include "Solution.h"

class AlgoGenetique : public AlgoAbstract
{
public:
    AlgoGenetique(Ennonce enonce, int population_size, int generations, double mutation_rate);

    void run() override;

private:
    /**
     * @brief Taille des populations
     * 
     */
    int population_size;

    /**
     * @brief Nombre de génération à réaliser
     * 
     */
    int generations;

    /**
     * @brief Fréquence des mutations
     * 
     */
    double mutation_rate;

    
    std::vector<std::vector<Item>> population;
    std::vector<double> fitness;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

    /**
     * @brief Crée la population initiale
     * 
     */
    void initialize_population();

    void evaluate_population();

    void selection();

    int tournament_selection();

    void crossover();

    void mutation();
    void save_best_solution();
};
