#include <iostream>
#include <fstream>
#include <string>
#include "Ennonce.h"
#include "Bin.h"
#include "Solution.h"

using namespace std;


void testBin()
{
    Ennonce m("data/binpacking2d/binpacking2d-02.bp2d");
    //m.printSpec();


    //test de bin
    Bin b(10,10);
    Item i1(12,12, 1);

    cout << b.fit(Coordinate(0,0),i1) <<endl; ; //true
    cout << b.freeSpace() << endl; //100
    cout << b.isFree(Coordinate(0,0)) << endl; //true





    std::ofstream outputFile("output.json");

    // Vérifier si le fichier est bien ouvert
    if (!outputFile.is_open()) {
        std::cerr << "Erreur à l'ouverture du fichier" << std::endl;
        return;
        }

    // Sérialiser l'objet Bin dans le fichier de sortie
    outputFile << "{\n";
    outputFile << "    \"bin\": ";
    b.serialize(outputFile);
    outputFile << "\n}";

    // Fermer le fichier
    outputFile.close();

    std::cout << "Sérialisation complétée avec succès dans output.json" << std::endl;}

void testjson()
{
    //test ecrit correctement dans le fichier à partir de solutio

    Solution s; 
    s.createNewBin(10,10);
    Item i1(1, 2, 3);
    s.setPosition(i1, Coordinate(0,0), s.listBin.front());

    s.createNewBin(10,10);
    Item i2(2, 3, 4);
    s.setPosition(i2, Coordinate(0,0), s.listBin.back());

    s.dumpToJson("output.json");


}

int main() {
    testjson();

    return 0;
    

    







}