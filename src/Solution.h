#pragma once
#include<list>
#include"Item.h"
#include"JsonWriter.h"
#include <map>
#include"Bin.h"


class Solution
{
private:
    std::list<Bin> listBin;
    std::map<Item, Bin*> map;


    std::list<Coordinate> listFreeCoordinates(Bin b);
    bool fit(Item i, Coordinate c, Bin b);

public:
    Solution();
    ~Solution();
    //fonction qui dumpjson
    void dumpToJson(const std::string& file_path) const;

    //fct emplacement valide
    //fct place qui fait appel à valide
    void setPosition(Item i, Coordinate c);
    
    void createNewBin();

    //renvoi liste coint hg 

    //l'ordre de prio est hauteur puis "gaucheur"
    

};
