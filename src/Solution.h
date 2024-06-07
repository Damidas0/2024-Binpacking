#pragma once
#include<list>
#include"Item.h"
#include"JsonWriter.h"
#include <map>
#include"Bin.h"


class Solution
{
private:
    //
    std::map<Item, Bin*> map;

public:
    Solution(/* args */);
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

Solution::Solution(/* args */)
{
}

Solution::~Solution()
{
}
