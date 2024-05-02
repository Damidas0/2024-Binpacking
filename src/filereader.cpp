#include <iostream>
#include <fstream>
#include <string>
#include "filereader.h"

int main() {
    std::ifstream file("data/binpacking2d/binpacking2d-01.bp2d");
    
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    
    file.close();
    
    return 0;
}

filereader::filereader(std::string file_path)
{
    std::ifstream file(file_path);
    
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    
}