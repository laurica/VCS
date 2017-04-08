#ifndef DIFFBUILDER
#define DIFFBUILDER

#include <string>
#include <vector>

#include "Diff.h"
#include "DiffElement.h"
#include "Line.h"

class DiffBuilder {
  unsigned int numberOfLastInsertedLine;
  std::vector<Line> insertedLines;
  unsigned int numberOfLastDeletedLine;
  std::vector<Line> deletedLines;
  std::vector<DiffElement> insertions;
  std::vector<DiffElement> deletions;

 public:
  void registerDeletedLine(const unsigned int index, const std::string& text);
  void registerInsertedLine(const unsigned int index, const std::string& text);
  Diff build();
};

#endif
