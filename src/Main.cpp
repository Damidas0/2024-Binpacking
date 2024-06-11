#include <iostream>
#include <fstream>
#include <string>
#include "Ennonce.h"

using namespace std;
int main() {

    Ennonce m("data/binpacking2d/binpacking2d-02.bp2d");
    cout<<m;
    m.dumpToJson("d.json");
    cout << "Hello, World!" << endl;
    return 0;
}