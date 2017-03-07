#include <fstream>

#include "FileWriter.h"

using namespace std;

void FileWriter::writeFile(vector<Line>& lines, string fileName) {
  ofstream file;
  file.open(fileName);

  for (Line line : lines) {
    file << line.getString() << endl;
  }

  file.close();
}
