#include <fstream>

#include "FileWriter.h"

using namespace std;

void FileWriter::writeFile(const char * fileName, const vector<string>& lines) {
  ofstream file;
  file.open(fileName);

  for (const string& line : lines) {
    file << line << endl;
  }

  file.close();
}
