#include <string>
#include "JsonWriter.h"


std::string JsonWriter::writeLine(std::string field, std::string val, bool lastLine, int offset)
{
    std::string res = "";
    for (int i = 0; i<=offset+1; i++){
        res+="    ";
    }
    res +=  "\"" + field + "\": \"" + val + "\"";
    if (!lastLine){
        res += ",\n";
    }else{
        res+="\n";
    }
    return res;
}

