#include "SimulatedAnnealing.h"
#include <random>  


SimulatedAnnealing::SimulatedAnnealing(Ennonce enonce): AlgoAbstract(enonce)
{
    initialize();
}

void SimulatedAnnealing::initialize()
{
    CurrentList = m_enonce.items;
    int bin_width = m_enonce.bin_width;
    int bin_height = m_enonce.bin_height;



    //on part de la solution de lalgo naif cad de lgfi avec une liste triée 

    this->CurrentList.sort([](Item a, Item b) { return a.getArea() > b.getArea(); });

    //on initialise lgfi
    LGFI_heuristic lgfi(this->CurrentList, bin_width, bin_height);
    
    this->m_solution = lgfi.solve();
    this->Current = this->m_solution;

    //paramètre de l'algo
    temperature = 5;
    lambda = 0.999;
    iterations = 500; 
}


std::list<Item> SimulatedAnnealing::generateNeighbor() {
    std::list<Item> neighbor = CurrentList; // Fait une copie de CurrentList

    if ((rand() % 3 == 0))
     {
        // Changer un paire d'items cote à cote et les échanger 
        if (neighbor.size() > 1) { // Assure qu'il y a au moins deux éléments
            auto it = neighbor.begin();
            std::advance(it, rand() % (neighbor.size() - 1)); // Sélectionne un élément aléatoire
            std::swap(*it, *std::next(it)); // Échange l'élément avec le suivant
        }
    } else {
        // Rotate un item aléatoire
        if (!neighbor.empty()) {
            auto it = std::next(neighbor.begin(), rand() % neighbor.size());
            it->rotate(); // Assurez-vous que votre classe Item a une méthode rotate()
        }
    }

    return neighbor;
}



void SimulatedAnnealing::run()
{   
    //debbug 
    int stats_better = 0;
    int stats_worse = 0;

    int compteur = 0;
    std::cout << "fitness de la solution initiale: " << Current.Fitness() << std::endl;

    while (temperature > 0.01)
    {   


        std::list<Item> neighbor = generateNeighbor();
        LGFI_heuristic lgfi(neighbor, m_enonce.bin_width, m_enonce.bin_height);
        Solution neighborSolution = lgfi.solve(); //solution de lgfi avec la liste neighbor
        double neighborFitness = neighborSolution.Fitness(); //fitness de la solution de lgfi avec la liste neighbor
        double currentFitness = Current.Fitness(); //fitness de la solution de lgfi avec la liste current
        double delta = neighborFitness - currentFitness;

        if (neighborFitness < currentFitness)
        {
            CurrentList = neighbor;
            Current = neighborSolution;

            stats_better++;

            if (this->m_solution.Fitness() > neighborFitness)
            {
                m_solution = Current;
                std::cout << "Nouvelle meilleure solution trouvée" << std::endl;
            }
        }
        else
        {   
            double p = exp(-delta / temperature); // on met pas de moins car delta est négatif
            double r = (double)rand() / RAND_MAX;
            if (p>r)
            {

                Current = neighborSolution;
                CurrentList = neighbor;
                stats_worse++;


            }
        }
        temperature *= lambda;
        compteur++;
        if (compteur % 10 == 0)
        {
            fitness_values.push_back(Current.Fitness());
        }
        if (compteur % 100 == 0)
        {
           

            std::cout << "------------Iteration: " << compteur << "----------------" << std::endl;
            std::cout << "Temperature: " << temperature << std::endl;
            std::cout << "Current fitness: " << Current.Fitness() << std::endl;
            std::cout << "Best solution " << m_solution.Fitness() << std::endl;

            std::cout << "nb de passage ou on prends une solution meilleure " << stats_better << "/100 " <<std::endl;
            std::cout << "nb de passage ou on prends une solution moins bonne " << stats_worse <<  "/100 " <<std::endl;
            stats_better = 0;
            stats_worse = 0;

        }
        if (compteur == iterations )
        {
            break;
        }
    }
    m_solution.dumpToJson("output.json");
    std::cout << "Solution dumped to output.json" << std::endl;

}


void SimulatedAnnealing::DumpFitnessValues(std::string file_path)
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

void SimulatedAnnealing::updateEnnonce(Ennonce enonce)
{
    m_enonce = enonce;
    initialize();
    std::cout << "Enoncé mis à jour" << std::endl;
}

