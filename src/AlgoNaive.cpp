#include "AlgoNaive.h"
#include "LGFI_heuristic.h"
#include <iostream>


void AlgoNaive::run() 
{
    std::list<Item> items = m_enonce.items;
    int bin_width = m_enonce.bin_width;
    int bin_height = m_enonce.bin_height;

    //on trie la liste d'items par ordre décroissant d'aire

    items.sort([](Item a, Item b) { return a.getArea() > b.getArea(); });

    //on initialise lgfi
    LGFI_heuristic lgfi(items, bin_width, bin_height);

    this->m_solution = lgfi.solve();
    this->m_solution.dumpToJson("output.json");

    std::cout << "fitness: " << this->m_solution.Fitness() << std::endl;

    std::cout << "Solution dumped to output.json" << std::endl;
    




}

