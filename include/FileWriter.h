#ifndef FILEWRITER
#define FILEWRITER

#include <string>
#include <vector>

#include "Line.h"

class FileWriter {
 public:
  static void writeFile(const char * fileName, const std::vector<std::string>& lines);
};

#endif
