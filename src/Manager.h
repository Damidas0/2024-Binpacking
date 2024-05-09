
#pragma once
#include<string>
#include<list>
#include "Item.h"
#include <ostream>


class Manager
{
private:
    //Variables
    std::string name; 
    std::string comment; 
    int nb_items; 
    int bin_width; 
    int bin_height; 
    std::list<Item> items; 

    //private functions
    void parse_file(std::string file_path);
    std::string getValue(std::string line);
    Item getItemFromLine(std::string line);
    std::vector<std::string> splitByWhitespace(const std::string& str);

public:

    Manager(std::string file_path);

    friend std::ostream &operator<<(std::ostream &out, Manager &m);


    
};




