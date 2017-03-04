#ifndef DIFFBUILDER
#define DIFFBUILDER

#include <vector>

#include "Diff.h"
#include "DiffElement.h"
#include "Line.h"

class DiffBuilder {
  int numberOfLastInsertedLine;
  std::vector<Line> insertedLines;
  int numberOfLastDeletedLine;
  std::vector<Line> deletedLines;
  std::vector<DiffElement> insertions;
  std::vector<DiffElement> deletions;

 public:
  void registerDeletedLine(const Line l);
  void registerInsertedLine(const Line l);
  Diff build();
};

#endif
