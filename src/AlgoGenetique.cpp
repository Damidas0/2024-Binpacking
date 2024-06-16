#include "AlgoGenetique.h"
#include "AlgoAbstract.h"

AlgoGenetique::AlgoGenetique(Ennonce enonce, int population_size, int generations, double mutation_rate) : AlgoAbstract(enonce)
{
    this->population_size = population_size;
    this->generations = generations;
    this->mutation_rate = mutation_rate;
}

void AlgoGenetique::run()
{
    initialize_population();
    for (int generation = 0; generation < generations; ++generation)
    {
        std::cout << generation;
        evaluate_population();
        selection();
        crossover();
        mutation();
    }
    save_best_solution();
}

void AlgoGenetique::initialize_population()
{
    // Convertissez la liste en vector
    std::vector<Item> items(m_enonce.items.begin(), m_enonce.items.end());

    std::cout << this->population_size << std::endl;
    std::cout << "Initialisation de la population..." << std::endl;

    for (int i = 0; i < this->population_size; ++i)
    {
        //std::cout << "Ab c d";
        std::shuffle(items.begin(), items.end(), rng);
        population.push_back(items);
    }
}

void AlgoGenetique::evaluate_population()
{
    fitness.clear();
    for (const auto &individual : population)
    {
        LGFI_heuristic lgfi(individual, m_enonce.bin_width, m_enonce.bin_height);
        Solution solution = lgfi.solve();
        fitness.push_back(solution.Fitness());
    }
}

void AlgoGenetique::selection()
{
    std::vector<std::vector<Item>> new_population;
    for (int i = 0; i < population_size; ++i)
    {
        int parent1 = tournament_selection();
        int parent2 = tournament_selection();
        new_population.push_back(fitness[parent1] > fitness[parent2] ? population[parent1] : population[parent2]);
    }
    population = std::move(new_population);
}

int AlgoGenetique::tournament_selection()
{
    int best = rng() % population_size;
    for (int i = 1; i < 3; ++i)
    { // Tournoi de taille 3
        int competitor = rng() % population_size;
        if (fitness[competitor] > fitness[best])
        {
            best = competitor;
        }
    }
    return best;
}

void AlgoGenetique::crossover()
{
    std::uniform_int_distribution<int> crossover_point_dist(1, m_enonce.items.size() - 1);
    for (int i = 0; i < population_size; i += 2)
    {
        if (i + 1 < population_size)
        {
            int crossover_point = crossover_point_dist(rng);
            auto &parent1 = population[i];
            auto &parent2 = population[i + 1];
            std::vector<Item> child1(parent1.begin(), parent1.begin() + crossover_point);
            std::vector<Item> child2(parent2.begin(), parent2.begin() + crossover_point);
            for (const auto &item : parent2)
            {
                if (std::find(child1.begin(), child1.end(), item) == child1.end())
                {
                    child1.push_back(item);
                }
            }
            for (const auto &item : parent1)
            {
                if (std::find(child2.begin(), child2.end(), item) == child2.end())
                {
                    child2.push_back(item);
                }
            }
            population[i] = std::move(child1);
            population[i + 1] = std::move(child2);
        }
    }
}

void AlgoGenetique::mutation()
{
    std::uniform_int_distribution<int> mutation_point_dist(0, m_enonce.items.size() - 1);
    for (auto &individual : population)
    {
        if (dist(rng) < mutation_rate)
        {
            int point1 = mutation_point_dist(rng);
            int point2 = mutation_point_dist(rng);
            std::swap(individual[point1], individual[point2]);
        }
    }
}

void AlgoGenetique::save_best_solution()
{
    auto best_it = std::max_element(fitness.begin(), fitness.end());
    int best_index = std::distance(fitness.begin(), best_it);
    LGFI_heuristic lgfi(population[best_index], m_enonce.bin_width, m_enonce.bin_height);
    Solution best_solution = lgfi.solve();
    best_solution.dumpToJson("best_solution.json");
}
