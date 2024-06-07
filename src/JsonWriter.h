#ifndef JSONWRITER_H
#define JSONWRITER_H
#include <string>

class JsonWriter
{
private:
public:
    std::string writeLine(std::string field, std::string val, bool lastLine=false, int offset=0);
};

#endif