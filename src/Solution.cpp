#include "Solution.h"
#include <fstream>
#include <iostream>


// bool Solution::fit(Item i, Coordinate c, Bin b)
// {
//     return b.fit(c);
// }

void Solution::createNewBin(int width, int height)
{
    Bin b(width, height);
    listBin.push_front(b);
    nbBins++;
}

int Solution::getNumberOfBins()
{
    return this->listBin.size();
}

//void Solution::add(Item i, Coordinate c, Bin &b)
float Solution::Fitness() const
{
    int res = nbBins; 
    //std::cout << "nbBins: " << nbBins << std::endl;
    float fillingLstBin = listBin.front().getArea() - listBin.front().freeSpace();
    float areaBin = listBin.front().getArea();
    float lastFilling = fillingLstBin/areaBin;

    
    // std::cout <<"freespace in last bin: " << listBin.front().freeSpace() << std::endl;
    // std::cout << "area of last bin: " << listBin.front().getArea() << std::endl;
    // std::cout << "lastFilling: " << lastFilling << std::endl;
    // std::cout << "fitness (nbBins -1 + lastFilling): " << res-1 + lastFilling << std::endl; //on mets le nombre de bins-1 comme ça on a un nombre de bins correct et on ajoute le remplissage de la dernière bin, pour avoir le nombre de bins total on arrondis au supérieur

    return res - 1  + lastFilling; 
}




Solution::Solution()
{
    nbBins = 0; 

}

Solution::~Solution()
{

}

void Solution::dumpToJson(const std::string& file_path) const {
    std::ofstream outputFile(file_path);

    if (outputFile.is_open()) {
        outputFile << "{\n";
        
        // Serialize bins
        outputFile << "    \"bins\": [\n";
        bool firstBin = true;
        for (const auto& bin : listBin) {
            if (!firstBin) {
                outputFile << ",\n";
            }
            outputFile << "        {\n";
            outputFile << "            \"dimensions\": {\n";
            outputFile << "                \"width\": " << bin.getWidth() << ",\n";
            outputFile << "                \"height\": " << bin.getHeight() << "\n";
            outputFile << "            },\n";
            outputFile << "            \"rectangles\": [\n";
            
            bool firstItem = true;
            for (const auto& item : bin.items) {
                if (!firstItem) {
                    outputFile << ",\n";
                }
                outputFile << "                {\n";
                outputFile << "                    \"id\": " << item.m_id << ",\n";
                outputFile << "                    \"width\": " << item.getWidth() << ",\n";
                outputFile << "                    \"height\": " << item.getHeight() << ",\n";
                outputFile << "                    \"x\": " << item.topLeft.getX() << ",\n"; 
                outputFile << "                    \"y\": " << item.topLeft.getY() << "\n";
                outputFile << "                }";
                firstItem = false;
            }
            
            outputFile << "\n            ]\n";
            outputFile << "        }";
            firstBin = false;
        }
        outputFile << "\n    ]\n";
        
        outputFile << "}\n";
        outputFile.close();
        std::cout << "JSON file has been saved\n";
    } else {
        std::cerr << "Unable to open the file for writing JSON dump.\n";
    }
}

