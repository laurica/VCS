#ifndef DIFF
#define DIFF

#include <vector>

#include "DiffElement.h"

class Diff {
  const std::vector<DiffElement> insertions;
  const std::vector<DiffElement> deletions;
 public:
  Diff(const std::vector<DiffElement> insertions,
       const std::vector<DiffElement> deletions);
  const std::vector<DiffElement>& getDeletions() const;
  const std::vector<DiffElement>& getInsertions() const;
  void print() const;
};

#endif
