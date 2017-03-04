#ifndef DIFF
#define DIFF

#include <vector>

#include "DiffElement.h"

class Diff {
  std::vector<DiffElement> insertions;
  std::vector<DiffElement> deletions;
 public:
  Diff(std::vector<DiffElement> insertions, std::vector<DiffElement> deletions);
  void print();
};

#endif
