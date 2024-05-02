#ifndef FILEREADER_H
#define FILEREADER_H
#include<string>
#include<list>
#include "bin.h"

class filereader
{
private:

    std::string name; 
    std::string comment; 
    int nb_items; 
    int bin_width; 
    int bin_height; 

    std::list<bin> items; 


public:

    filereader(std::string file_path);
    
};




#endif FILREADER_h