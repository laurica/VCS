#ifndef FILEPARSER
#define FILEPARSER

#include <fstream>
#include <vector>
#include "Line.h"

class FileParser 
{
public:
    static void readFile(const std::string fileName, std::vector<Line>& linesInFile);
};

#endif
