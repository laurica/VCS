#include <vector>

#include "DiffInterface.h"
#include "FileParser.h"
#include "Line.h"
#include "SubsequenceAnalyzer.h"

using namespace std;

FileDiff DiffInterface::calculateFileDiff(const char * previousCommitFileName,
					  const char * fileName) {
  vector<Line> originalFile;
  vector<Line> newFile;

  FileParser::readFile(previousCommitFileName, originalFile);
  FileParser::readFile(fileName, newFile);

  FileDiff diff = SubsequenceAnalyzer::calculateDiff(originalFile, newFile);

  return diff;
}
