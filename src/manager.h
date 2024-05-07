
#pragma once
#include<string>
#include<list>
#include "Item.h"
#include <string>

class Manager
{
private:

    std::string name; 
    std::string comment; 
    int nb_items; 
    int bin_width; 
    int bin_height; 

    

    std::list<Item> items; 
    void parse_file(std::string file_path);


public:

    Manager(std::string file_path);

    
};




