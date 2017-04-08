#ifndef DIFF
#define DIFF

#include <string>
#include <vector>

#include "FileDiff.h"

class Diff {
  std::vector<std::pair<std::string, std::vector<std::string> > > addedFiles;
  std::vector<std::string> deletedFiles;
  std::vector<std::pair<std::string, FileDiff> > diffs;
};

#endif
