#ifndef FILEPARSER
#define FILEPARSER

#include <fstream>
#include <vector>
#include "Line.h"

class FileParser 
{
public:
    void readFile(std::string fileName, std::vector<Line>& linesInFile);
};

#endif
