#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Item.h"
#include "Manager.h"

Manager::Manager(std::string file_path) {
    parse_file(file_path);   
}

void Manager::parse_file(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }
    int line_number = 0;

    while (std::getline(file, line)) {
        if (line_number>6){
            items.push_back(getItemFromLine(line));
        }else{
            switch (line_number){
            case 0:
                name = getValue(line);
                break;
            case 1:
                comment = getValue(line);
                break;
            case 2:
                nb_items = std::stoi(getValue(line));
                break;
            case 3:
                bin_width = std::stoi(getValue(line));
                break;
            case 4:
                bin_height = std::stoi(getValue(line));
                break;
            default:
                break;
            }
        }    
        
        line_number++;

    }


    // Json::Value root;
    // file >> root; // a partir de là tout est dans root 

    // name = root["NAME"].asString();
    // comment = root["COMMENT"].asString();
    // nb_items = root["NB_ITEMS"].asInt();
    // bin_height = root["BIN_HEIGHT"].asInt();
    // bin_width = root["BIN_WIDTH"].asInt();

    // for (int i = 0; i < nb_items; i++) {
    //     Item item(root["ITEMS"][i]["WIDTH"].asInt(), root["ITEMS"][i]["HEIGHT"].asInt(), root["ITEMS"][i]["ID"].asInt());
    //     items.push_back(item);
    // }
}

std::string Manager::getValue(std::string line)
{
        // Recherche de la position du caractère ":" dans la ligne
    size_t pos = line.find(":");
    
    if (pos != std::string::npos) {
        // Extraction de la sous-chaîne après le caractère ":"
        std::string value = line.substr(pos + 1);
        
        // Suppression des espaces inutiles
        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);
        
        return value;
    } else {
        return "";
    }
}

Item Manager::getItemFromLine(std::string line)
{
    //split line 
    std::vector<std::string> tokens = splitByWhitespace(line);
    //construct Item 
    return (Item(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2])));
}

std::vector<std::string> Manager::splitByWhitespace(const std::string &str){
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}


std::ostream &operator<<(std::ostream &out, Manager &m)
{
    out << "Name: " << m.name << std::endl;
    out << "Comment: " << m.comment << std::endl;
    out << "Number of items: " << m.nb_items << std::endl;
    out << "Bin width: " << m.bin_width << std::endl;
    out << "Bin height: " << m.bin_height << std::endl;

    // Imprimer les éléments de la liste
    out << "Items:" << std::endl;
    for(const Item item : m.items)
    {
        out << " - " << item << std::endl;
    }

    return out;
    }
