#include <iostream>
#include <fstream>
#include <string>
#include "Manager.h"

using namespace std;
int main() {

    Manager m("data/binpacking2d/binpacking2d-02.bp2d");
    cout<<m;
    m.dumpToJson("d.json");
    return 0;
}