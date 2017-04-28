#ifndef FILEDIFF
#define FILEDIFF

#include <iostream>
#include <vector>

#include "DiffElement.h"

class FileDiff {
  const std::vector<DiffElement> insertions;
  const std::vector<DiffElement> deletions;
 public:
  FileDiff(const std::vector<DiffElement> insertions,
	   const std::vector<DiffElement> deletions);
  const std::vector<DiffElement>& getDeletions() const;
  const std::vector<DiffElement>& getInsertions() const;
  void print(const std::string& path) const;
  bool isEmptyDiff() const;
};

#endif
