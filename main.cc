#include <iostream>
#include <vector>

#include "Diff.h"
#include "DiffApplier.h"
#include "FileParser.h"
#include "FileWriter.h"
#include "Line.h"
#include "SubsequenceAnalyzer.h"

int main() {
  std::vector<Line> u;
  std::vector<Line> v;
  std::vector<Line> w;

  FileParser::readFile("examples/baseline.cpp", u);
  FileParser::readFile("examples/diff1.cpp", v);
  FileParser::readFile("examples/diff2.cpp", w);

  Diff d1 = SubsequenceAnalyzer::calculateDiff(u, v);
  Diff d2 = SubsequenceAnalyzer::calculateDiff(v, w);

  d1.print();
  
  std::vector<Line> newFile;
  DiffApplier::applyDiff(u, d1, newFile);
  FileWriter::writeFile(newFile, "testing01.txt");
  
  //DiffApplier::mergeDiffs(d1, d2);
      
  return 0;
}
