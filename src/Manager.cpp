#include <iostream>
#include <fstream>
// #include "json/json.h"
#include <vector>
#include "Item.h"
#include "Manager.h"

Manager::Manager(std::string file_path) {

    parse_file(file_path);
    

   
}

void Manager::parse_file(std::string file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;

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




