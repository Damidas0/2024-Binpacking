#include <iostream>
#include <fstream>
#include <string>
#include "Ennonce.h"
#include "Bin.h"
#include "Solution.h"
#include "AlgoNaive.h"
#include "FreeSpace.h"
#include "Testing.h"
#include "SimulatedAnnealing.h"
#include "TabouSearch.h"

using namespace std;

//variable globale du main 
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


 

// void testLGFI()
// {
//     //test de LGFI
//     Ennonce m("data/binpacking2d/binpacking2d-04.bp2d");
//     m.printSpec();


//     AlgoNaive a(m);
//     a.run();
//     a.m_solution.dumpToJson("results/output.json");





// }

// void testNaive()
// {
//     AlgoNaive algo(Ennonce("data/binpacking2d/binpacking2d-00.bp2d")); //pour l'instant on lui donne un faux path mais il faudra faire le contructeur par défaut

//     std::string file_path = "results/resultsNaive_StrategyshorterLeftover.json";

//     Testing tester;
//     tester.dumpSolutionAllInstances(algo, file_path);


// }
// void testFit()
// {
//     FreeSpace fs = FreeSpace(5, 5, Coordinate(0, 0));
//     Item i1(1, 5, 5);
//     bool rotate = false;
//     cout << fs.fitGlobal(i1, rotate) << endl;

// }
// void testSimulatedAnnealing()
// {

//     Ennonce m("data/binpacking2d/binpacking2d-02.bp2d");
//     m.printSpec();
//     SimulatedAnnealing algo(m);

//     algo.run();
//     algo.m_solution.dumpToJson("results/output.json");












// }

// void testing()
// {   

//     SimulatedAnnealing algo(Ennonce("data/binpacking2d/binpacking2d-00.bp2d"));
//     Testing test; 
//     test.dumpSolutionAllInstances(algo, "results/resultsSimulatedAnnealingAllinstances.json");
// }



void annealing(int num) // on rentre vraiment le numéro pas l'index
{
    assert (num > 0 && num <=13);
    Ennonce m(instances[num-1]);
    m.printSpec();
    SimulatedAnnealing algo(m);

    algo.run();
    algo.m_solution.dumpToJson("results/output.json");
    algo.DumpFitnessValues("results/fitness_values.json");
    std::cout << "fitness : " << algo.m_solution.Fitness() << std::endl;
}

void Naive(int num) // on rentre vraiment le numéro pas l'index
{
    assert (num > 0 && num <=13);
    Ennonce m(instances[num-1]);
    m.printSpec();
    AlgoNaive algo(m);

    algo.run();
    algo.m_solution.dumpToJson("results/output.json");
    std::cout << "fitness : " << algo.m_solution.Fitness() << std::endl;
}

void testNaive()
{
    Ennonce m("data/binpacking2d/binpacking2d-01.bp2d"); //peu importe le path ici il sera mis à jour par la suite
    m.printSpec();
    AlgoNaive algo(m);

    std::string file_path = "results/resultsNaive_StrategylongerLeftover.json";

    Testing tester;
    tester.dumpSolutionAllInstances(algo, file_path);
}

void testAnnealing()
{
    Ennonce m("data/binpacking2d/binpacking2d-01.bp2d"); //peu importe le path ici il sera mis à jour par la suite
    m.printSpec();
    SimulatedAnnealing algo(m);

    std::string file_path = "results/resultsAnnealing.json";

    Testing tester;
    tester.dumpSolutionAllInstances(algo, file_path);
}

void Tabou(int num) // on rentre vraiment le numéro pas l'index
{
    assert (num > 0 && num <=13);
    Ennonce m(instances[num-1]);
    m.printSpec();
    TabouSearch algo(m);

    algo.run();
    algo.m_solution.dumpToJson("results/output.json");
    algo.DumpFitnessValues("results/fitness_values.json");
    std::cout << "fitness : " << algo.m_solution.Fitness() << std::endl;
}

int main() {

    Tabou(4);
}