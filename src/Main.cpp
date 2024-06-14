#include <iostream>
#include <fstream>
#include <string>
#include "Ennonce.h"
#include "Bin.h"
#include "Solution.h"
#include "AlgoNaive.h"
#include "FreeSpace.h"

using namespace std;



 

void testLGFI()
{
    //test de LGFI
    Ennonce m("data/binpacking2d/binpacking2d-00.bp2d");
    m.printSpec();

    AlgoNaive a(m);
    a.run();




}

void testBin()
{
    //test de Bin
    Bin b(10, 10);
    Item i1(1, 5, 5);
    Item i2(2, 5, 5);
    Item i3(3, 5, 5);
    Item i4(4, 5, 5);

    b.add(i1, Coordinate(0, 0));
    b.printIsFree();
    cout << "-------------------" << endl;
    cout << b.fit(Coordinate(5, 0), i2) << endl;
    b.add(i2, Coordinate(5, 0));
    b.printIsFree();
    cout << "-------------------" << endl;

    b.add(i3, Coordinate(0, 5));
    b.printIsFree();
    cout << "-------------------" << endl;

    b.add(i4, Coordinate(5, 5));
    b.printIsFree();
    cout << "-------------------" << endl;


    Bin b2(5,5); 
    b2.printIsFree();
    cout << "-------------------" << endl;
    b2.add(i1, Coordinate(0, 0));
    b2.printIsFree();

 


}
int main() {
    testLGFI();

    return 0;
    

    







}