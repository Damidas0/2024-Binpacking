
#pragma once
#include<string>
#include<list>
#include "Item.h"
#include <ostream>
#include <vector>



class Ennonce
{
private:

    //private functions
    void parse_file(std::string file_path);
    std::string getValue(std::string line);
    Item getItemFromLine(std::string line);
    std::vector<std::string> splitByWhitespace(const std::string& str);

public:
        //Variables on les mets en publique pour l'instant
    /**
     * @brief Nom de l'instance
     */
    std::string name; 
    /**
     * @brief Commentaire de l'instance
     */
    std::string comment; 
    /**
     * @brief Nombre d'items
     */
    int nb_items; 
    int bin_width; 
    int bin_height;
    /**
     * @brief Liste des items à placer
     */
    std::list<Item> items; 
    std::list<Item> getItems(); 
    Ennonce(std::string file_path);
    void printSpec();
    friend std::ostream &operator<<(std::ostream &out, Ennonce &m);
    void dumpToJson(const std::string& file_path) const;

};



