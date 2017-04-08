#ifndef FILEWRITER
#define FILEWRITER

#include <string>
#include <vector>

#include "Line.h"

class FileWriter {
 public:
  static void writeFile(std::vector<Line>& lines, std::string fileName);
};

#endif
