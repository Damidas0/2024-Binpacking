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
    outputFile << "\n}";

    // Fermer le fichier
    outputFile.close();

    std::cout << "Sérialisation complétée avec succès dans output.json" << std::endl;}

void testjson()
{
    //test ecrit correctement dans le fichier à partir de solutio

    Solution s; 
    s.createNewBin(10,10);
    s.createNewBin(10,10);


    //ajout de plein d'item pour faire un beau json de test

    Item i1 (1,2,3);
    Item i2 (2,3,4);
    Item i3 (3,4,5);
    Item i4 (4,5,6);
    Item i5 (5,6,7);
    Item i6 (6,7,8);


    s.setPosition(i1, Coordinate(0,0), s.listBin.front());
    //s.listBin.front().printIsFree();

    s.setPosition(i2, Coordinate(5,5), s.listBin.front());
    s.listBin.front().printIsFree();

    s.setPosition(i3, Coordinate(0,0), s.listBin.back());
    s.setPosition(i4, Coordinate(5,5), s.listBin.back());
    
    s.dumpToJson("output.json");


}

int main() {
    testjson();

    return 0;
    

    







}