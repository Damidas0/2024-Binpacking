#include <iostream>
#include <fstream>
#include <string>
#include "Ennonce.h"
#include "Bin.h"
#include "Solution.h"
#include "AlgoNaive.h"

using namespace std;



 

void testLGFI()
{
    //test de LGFI
    Ennonce m("data/binpacking2d/binpacking2d-00.bp2d");
    m.printSpec();

    AlgoNaive a(m);
    a.run();




}
int main() {
    testLGFI();

    return 0;
    

    







}