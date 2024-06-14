#include "Solution.h"
#include <fstream>
#include <iostream>


bool Solution::fit(Item i, Coordinate c, Bin b)
{
    return b.fit(c, i);
}

void Solution::createNewBin(int width, int height)
{
    Bin b(width, height);
    listBin.push_front(b);
}

void Solution::add(Item i, Coordinate c, Bin &b)
{
    if (b.fit(c, i)) {


        map[i] = &b;
        b.items.push_back(i);

        for (int x = c.getX(); x < c.getX() + i.getWidth(); x++) {
            for (int y = c.getY(); y <c.getY() + i.getHeight(); y++) {
                b.is_free[x][y] = false;
            }
        }
    }
    else 
    {   

        std::cerr << "Item cannot be placed at the given coordinates : (" << c.getX() << ", " << c.getY() << ")\n";
    }
}

Solution::Solution()
{

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

