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



 

void testLGFI()
{
    //test de LGFI
    Ennonce m("data/binpacking2d/binpacking2d-04.bp2d");
    m.printSpec();


    AlgoNaive a(m);
    a.run();





}

void testNaive()
{
    AlgoNaive algo(Ennonce("data/binpacking2d/binpacking2d-00.bp2d")); //pour l'instant on lui donne un faux path mais il faudra faire le contructeur par défaut

    std::string file_path = "results/resultsNaive_StrategyshorterLeftover.json";

    Testing tester;
    tester.dumpSolutionAllInstances(algo, file_path);


}
void testFit()
{
    FreeSpace fs = FreeSpace(5, 5, Coordinate(0, 0));
    Item i1(1, 5, 5);
    bool rotate = false;
    cout << fs.fitGlobal(fs.topLeft, i1, rotate) << endl;

}
void testSimulatedAnnealing()
{


    SimulatedAnnealing algo(Ennonce("data/binpacking2d/binpacking2d-01.bp2d"));
    algo.run();
    algo.m_solution.dumpToJson("results/outputs");











}

void testing()
{   

    SimulatedAnnealing algo(Ennonce("data/binpacking2d/binpacking2d-00.bp2d"));
    Testing test; 
    test.dumpSolutionAllInstances(algo, "results/resultsSimulatedAnnealingAllinstances.json");
}


int main() {
    testSimulatedAnnealing();


}