#include "FileParser.h"
#include <fstream>
#include <iostream>

using namespace std;

void FileParser::readFile(const string fileName, vector<Line>& linesInFile) 
{
    ifstream infile(fileName.c_str());
    string line;

    int i = 0;

    while (getline(infile, line)) {
        linesInFile.push_back(Line(i, line));
        ++i;
    }
}
