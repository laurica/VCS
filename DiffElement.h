#ifndef DIFFELEMENT
#define DIFFELEMENT

#include <vector>

#include "Line.h"

enum ElementType {
  INSERTION,
  DELETION
};

class DiffElement {
  ElementType type;
  std::vector<std::string> lines;
  int startingLine;
 public:
  DiffElement(ElementType type, std::vector<Line>& linesToAdd);
  void print();
};

#endif
