#ifndef DIFFELEMENT
#define DIFFELEMENT

#include <vector>

#include "Line.h"

enum ElementType {
  INSERTION,
  DELETION
};

class DiffElement {
  const ElementType type;
  std::vector<std::string> lines;
  int startingLine;
 public:
  DiffElement(const ElementType type, const std::vector<Line>& linesToAdd);
  void print() const;
};

#endif
