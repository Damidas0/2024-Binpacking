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

    cout << b.listFreeCoordinates().size() << endl; //1 le coin en haut à gauche uniquement




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

void testSolution()
{
    Ennonce m("data/binpacking2d/binpacking2d-02.bp2d");
    //m.printSpec(); 

    //création d'une solution
    Solution s;
    s.createNewBin(10,10);

    //placement des items
    Item i1(5, 5, 1);
    Item i2(3, 3, 2);

    cout << s.listBin.empty() << endl; //false
    s.setPosition(i1, Coordinate(0,0), s.listBin.front());

    cout << s.listBin.size() << endl; //1

    s.listBin.front().printIsFree(); //affiche la grille is_free

    cout << s.listBin.front().isFree(Coordinate(0,0)) << endl; //false


    s.dumpToJson("output.json");

    cout << "Sérialisation complétée avec succès dans output.json" << endl;





}

int main() {
    testSolution();

    return 0;
    

    







}