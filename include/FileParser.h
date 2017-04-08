#ifndef FILEPARSER
#define FILEPARSER

#include <fstream>
#include <vector>
#include "Line.h"

class FileParser 
{
public:
  static void readFile(const char * fileName,
		       std::vector<Line>& linesInFile);
  static void readFile(const char * fileName,
		       std::vector<std::string>& linesInFile);
};

#endif
