#include "FileParser.h"
#include <fstream>
#include <iostream>

using namespace std;

void FileParser::readFile(const char * fileName, vector<Line>& linesInFile) {
    ifstream infile(fileName);
    string line;

    int i = 0;

    while (getline(infile, line)) {
        linesInFile.push_back(Line(i, line));
        ++i;
    }
}

void FileParser::readFile(const char * fileName, vector<string>& linesInFile) {
  ifstream infile(fileName);
  string line;

  while (getline(infile, line)) {
    linesInFile.push_back(line);
  }
}
