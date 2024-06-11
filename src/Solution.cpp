#include "Solution.h"
#include <fstream>
#include <iostream>

std::list<Coordinate> Solution::listFreeCoordinates(Bin b)
{
    return b.listFreeCoordinates();
}

bool Solution::fit(Item i, Coordinate c, Bin b)
{
    return b.fit(c, i);;
}

void Solution::createNewBin(int width, int height)
{
    Bin b(width, height);
    listBin.push_back(b);
}

Solution::Solution()
{

}

Solution::~Solution()
{

}

void Solution::dumpToJson(const std::string &file_path) const
{
    std::ofstream outputFile(file_path);
    JsonWriter j;
    if (outputFile.is_open()) {
        outputFile << "{\n";
        outputFile << j.writeLine("listBin_size", std::to_string(listBin.size()));
        outputFile << j.writeLine("map_size", std::to_string(map.size()));

        // Serialize bins
        outputFile << "\n    \"bins\":\n    [\n";
        bool firstBin = true;
        for (const auto& bin : listBin) {
            if (!firstBin) {
                outputFile << ",\n";
            }
            // Assuming Bin has a serialize method similar to Item
            bin.serialize(outputFile);  
            firstBin = false;
        }
        outputFile << "\n    ],\n";

        // Serialize items and their bin mapping
        outputFile << "\n    \"item_bin_mapping\":\n    {\n";
        bool firstMapping = true;
        for (const auto& pair : map) {
            if (!firstMapping) {
                outputFile << ",\n";
            }
            //outputFile << "        \"" << pair.first.getName() << "\": \"" << pair.second->getId() << "\""; // Assuming Item has getName() and Bin has getId() methods
            firstMapping = false;
        }
        outputFile << "\n    }\n";

        outputFile << "}\n";
        outputFile.close();
        std::cout << "JSON file has been saved\n";
    } else {
        std::cerr << "Unable to open the file for writing JSON dump.\n";
    }

}
